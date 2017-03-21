/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:48:20 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/21 12:11:18 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "exec_redir.h"

/*
 ** This set of functions need to evolve to cover all cases of tree
 ** architecture. Right now it is unclear what functions are doing.
 ** Also need to insert builtin etc.
 */

void	apply_redir(t_list *lst)
{
	if (lst)
		get_redir(lst);
}

void	execute_cmd(t_ast *tree, t_sh *sh)
{
	//apply_redir(tree->redir);
	char	*path;
	char	**tab_path;
	int		i;

	i = 0;
	if (!ft_strchr(tree->args[0], '/'))
	{
		path = getenv("PATH");
		tab_path = ft_strsplit(path, ':');
		while (tab_path[i])
		{
			if (!(path = ft_build_path(tab_path[i], tree->args[0])))
				return ;
			execve(path, tree->args, sh->env);
			i++;
		}
	}
	else
		execve(tree->args[0], tree->args, sh->env);
}

void	run_pipe(t_ast *tree, int in_fd, t_sh *sh)
{
	int		pdes[2];
	pid_t	child;

	pipe(pdes);
	child = fork();
	if ((int)child == -1)
		return ;
	else if ((int)child == 0)
	{
		close(pdes[READ_END]);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		execute_cmd(tree->left, sh);
		exit(1);
	}
	close(pdes[WRITE_END]);
	wait(NULL);
	if (tree->right->type == PIPE_NODE)
		run_pipe(tree->right, pdes[READ_END], sh);
	else
	{
		dup2(pdes[READ_END], STDIN_FILENO);
		execute_cmd(tree->right, sh);
		close(pdes[READ_END]);
	}
}

void	handle_pipe_node(t_ast *tree, t_sh *sh)
{
	pid_t	child;

	if (!tree)
		return ;
	child = fork();
	if ((int)child == -1)
		return ;
	else if ((int)child == 0)
	{
		if (tree->type == PIPE_NODE)
			run_pipe(tree, STDIN_FILENO, sh);
		else
			execute_cmd(tree, sh);
	}
	wait(NULL);
}

void	execute(t_ast *tree, t_sh *sh)
{
	if (!tree)
		return ;
	if (tree->type == SEQ_NODE)
	{
		handle_pipe_node(tree->left, sh);
		execute(tree->right, sh);
	}
	else
		handle_pipe_node(tree, sh);
}
