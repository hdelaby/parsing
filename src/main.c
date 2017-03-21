/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 08:56:41 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/21 09:16:32 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"
#include "execution.h"
#include "line_edition.h"

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

char	*get_input(void)
{
	char	*str;

	str = NULL;
	if (!isatty(STDIN_FILENO))
	{
		if (get_next_line(STDIN_FILENO, &str) > 0)
			return (str);
		return (NULL);
	}
	ft_putstr_fd("21sh &> ", 0);
	return (line_editing());
}

int		main(void)
{
	t_list	*lst;
	char	*cmd;
	t_ast	*tree;

	while (42)
	{
		tree = NULL;
		cmd = get_input();
		if (!cmd)
			break ;
		if (!ft_strcmp(cmd, "exit\n"))
			break ;
		if ((lst = lex_cmd(cmd)))
		{
			tree = parser(lst);
			ft_lstdel(&lst, &ft_lstdelstr);
		}
		free(cmd);
		if (!tree)
			return (1);
		execute(tree);
		astdel(&tree);
	}
	/* display_tree(tree); */
}
