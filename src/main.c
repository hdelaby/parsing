/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 08:56:41 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/10 16:28:43 by hdelaby          ###   ########.fr       */
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

int		main(void)
{
	t_list	*lst;
	char	*cmd;
	t_ast	*tree;

	tree = NULL;
	/* ft_putstr("21sh $> "); */
	cmd = line_editing();
	/* cmd = ft_strdup("/bin/ls -l\n"); */
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
	/* display_tree(tree); */
}
