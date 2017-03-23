/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 08:56:41 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/23 13:15:10 by hdelaby          ###   ########.fr       */
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

	/* int	pfd[2]; */
	/* pid_t	pid; */
	/* char *cmd2[] = { "/bin/cat", 0 }; */
	/* char *cmd3[] = { "/bin/ls", "-l", 0 }; */

	/* pipe(pfd); */
	/* pid = fork(); */
	/* if ((int)pid == 0) */
	/* { */
	/* 	close(pfd[1]); */
	/* 	dup2(pfd[0], STDIN_FILENO); */
	/* 	execve("/bin/cat", cmd2, NULL); */
	/* } */
	/* else */
	/* { */
	/* 	close(pfd[0]); */
	/* 	dup2(pfd[1], STDOUT_FILENO); */
	/* 	execve("/bin/ls", cmd3, NULL); */
	/* } */
	/* exit (0); */
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
