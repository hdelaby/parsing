/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 08:56:41 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/06 10:01:46 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ast.h"
#include "execution.h"

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
	cmd = ft_strdup("/bin/ls -l | /usr/bin/wc -l ; /bin/echo lol ; /bin/echo mdr | /bin/cat -e\n");
	if ((lst = lex_cmd(cmd)))
	{
		tree = parser(lst);
		ft_lstdel(&lst, &ft_lstdelstr);
	}
	free(cmd);
	if (!tree)
		return (1);
	execute(tree);
	/* display_tree(tree); */
}
