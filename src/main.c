/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 08:56:41 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/25 17:43:57 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"
#include "execution.h"
#include "line_edition.h"
#include "shell.h"
#include "environ.h"

#include <stdio.h>

char	*get_input(t_sh *sh)
{
	char			*str;

	str = NULL;
	if (!isatty(STDIN_FILENO))
	{
		if (get_next_line(STDIN_FILENO, &str) > 0)
			return (str);
		return (NULL);
	}
	ft_putstr_fd("21sh &> ", 0);
	str = line_editing(&sh->hist);
	sh->hist = ft_dlstgethead(sh->hist);
	ft_dlstadd(&sh->hist, ft_dlstnew(str, ft_strlen(str) + 1));
	return (str);
}

void	feed_sh(t_sh *sh, char **environ)
{
	ft_bzero(sh, sizeof(t_sh));
	sh->env = ft_tabcpy(environ);
}

int		main(int argc, char **argv, char **environ)
{
	t_list	*lst;
	char	*cmd;
	t_ast	*tree;
	t_sh	sh;

	/* char	*cmd1[] = {"/bin/cat", NULL}; */
	char	*cmd2[] = {"/bin/cat", "/dev/random", NULL};
	char	*cmd3[] = {"/usr/bin/head", "-c", "100", NULL};
	int		fd1[2];
	/* int		fd2[2]; */

	pid_t	child;
	if (!(child = fork()))
	{
		pipe(fd1);
		if (!fork())
		{
			close(fd1[0]);
			dup2(fd1[1], STDOUT_FILENO);
			execve(cmd2[0], cmd2, environ);
			/* close(fd1[1]); */
			/* pipe(fd2); */
			/* if (!fork()) */
			/* { */
			/* 	close(fd2[0]); */
			/* 	dup2(fd2[1], STDOUT_FILENO); */
			/* 	execvp(cmd1[0], cmd1); */
			/* } */
			/* else */
			/* { */
			/* 	close(fd2[1]); */
			/* 	dup2(fd2[0], STDIN_FILENO); */
			/* 	execvp(cmd2[0], cmd2); */
			/* } */
		}
		else
		{
			close(fd1[1]);
			dup2(fd1[0], STDIN_FILENO);
			execvp(cmd3[0], cmd3);
		}
	}
	else
		waitpid(child, NULL, 0);
	exit(0);
	(void)argc;
	(void)argv;
	feed_sh(&sh, environ);
	while (42)
	{
		tree = NULL;
		cmd = get_input(&sh);
		if (!cmd)
			break ;
		if ((lst = lex_cmd(cmd)))
		{
			tree = parser(lst);
			ft_lstdel(&lst, &ft_lstdelstr);
		}
		free(cmd);
		if (!tree)
			return (1);
		execute(tree, &sh);
		astdel(&tree);
	}
	return (sh.status > 0 ? sh.status + 128 : 0);
	/* display_tree(tree); */
}

void	display_tree(t_ast *tree)
{
	if (!tree)
		return ;
	if (tree->type == ARG_NODE)
		ft_putlst(tree->redir);
	else
	{
		ft_putnbr(tree->type);
		ft_putchar('\n');
	}
	display_tree(tree->left);
	display_tree(tree->right);
}
