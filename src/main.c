/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 08:56:41 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/02 14:01:19 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ast.h"
#include <fcntl.h>

#define READ_END	0
#define WRITE_END	1

void	execute(t_ast *tree, int fd[3]);

void	apply_redir(t_list *lst, int fd[3])
{
	int		fildes;
	(void)fd;

	while (lst)
	{
		lst = lst->next;
		fildes = open(lst->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fildes, STDOUT_FILENO);
		lst = lst->next;
	}
}

void	execute_cmd(t_ast *tree, int fd[3])
{
	char	**cmd;

	(void)fd;
	cmd = ft_lst_to_tab(tree->args);
	apply_redir(tree->redir, fd);
	execve(cmd[0], cmd, NULL);
}

void	run_pipe(t_ast *tree, int fd[3])
{
	int		pdes[2];
	pid_t	child;

	/* ft_putnbr_fd(fd[0], 2); */
	/* ft_putnbr_fd(fd[1], 2); */
	/* ft_putnbr_fd(fd[2], 2); */
	/* ft_putchar_fd('\n', 2); */
	pipe(pdes);
	child = fork();
	if ((int)child == -1)
		return ;
	else if ((int)child == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		/* close(fd[0]); */
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		close(pdes[READ_END]);
		fd[1] = pdes[WRITE_END];
		execute_cmd(tree->left, fd);
		exit(1);
	}
	dup2(pdes[READ_END], fd[0]);
	close(pdes[WRITE_END]);
	fd[0] = pdes[READ_END];
	wait(NULL);
	if (tree->right->type == PIPE_NODE)
		run_pipe(tree->right, fd);
	else
		execute_cmd(tree->right, fd);
}

void	execute(t_ast *tree, int fd[3])
{
	pid_t	child;

	if (!tree)
		return ;
	child = fork();
	if ((int)child == -1)
		return ;
	else if ((int)child == 0)
		run_pipe(tree, fd);
	wait(NULL);
}

void	display_tree(t_ast *tree)
{
	if (!tree)
		return ;
	if (tree->type == ARG_NODE)
	{
		ft_putlst(tree->redir);
	}
	else
	{
		ft_putnbr(tree->type);
		ft_putchar('\n');
	}
	display_tree(tree->left);
	display_tree(tree->right);
}

int		main(void)
{
	t_list	*lst;
	char	*cmd;
	t_ast	*tree;
	int		fd[3];

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	fd[2] = STDERR_FILENO;
	cmd = ft_strdup("/bin/ls -l | /bin/cat -e | /bin/cat");
	lst = lex_cmd(cmd);
	free(cmd);
	tree = parser(lst);
	if (!tree)
		return (1);
	execute(tree, fd);
	/* display_tree(tree); */
}
