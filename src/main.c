/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 08:56:41 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/21 12:07:35 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"
#include "execution.h"
#include "line_edition.h"
#include "shell.h"

char	*get_input(void)
{
	char			*str;
	static t_dlist	*hist;

	str = NULL;
	hist = NULL;
	if (!isatty(STDIN_FILENO))
	{
		if (get_next_line(STDIN_FILENO, &str) > 0)
			return (str);
		return (NULL);
	}
	ft_putstr_fd("21sh &> ", 0);
	return (line_editing());
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

	(void)argc;
	(void)argv;
	feed_sh(&sh, environ);
	while (42)
	{
		tree = NULL;
		cmd = get_input();
		if (!cmd || !ft_strcmp(cmd, "exit\n"))
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
