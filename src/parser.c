/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 08:58:46 by hdelaby           #+#    #+#             */
/*   Updated: 2017/02/28 17:29:48 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ast.h"

t_ast	*list(t_list **tok);

void	parsing_error(char *str)
{
	ft_putstr_fd("Parsing error at ", 2);
	ft_putendl_fd(str, 2);
}

int		eat(t_list **tok, int type)
{
	if ((*tok)->content_size == (size_t)type)
		*tok = (*tok)->next;
	else
		return (1);
	return (0);
}

t_ast	*job(t_list	**tok)
{
	t_ast	*new_node;
	t_ast	*arg_list;

	arg_list = list(tok);
	if (arg_list && (*tok)->content_size == PIPE)
	{
		if (eat(tok, PIPE))
			return (NULL);
		if (!(new_node = ast_node(PIPE, arg_list, NULL)))
			return (NULL);
		new_node->right = job(tok);
		return (new_node);
	}
	return (arg_list);
}

t_ast	*list(t_list **tok)
{
	t_ast	*new_node;

	if (!(new_node = ast_leaf(ARG_NODE)))
		return (NULL);
	while ((*tok)->content_size == WORD || (*tok)->content_size == OREDIR)
	{
		if ((*tok)->content_size == WORD)
		{
			ft_lstaddback(&new_node->args, ft_lstnew((*tok)->content,
						ft_strlen((*tok)->content) + 1));
			if (eat(tok, WORD))
				return (NULL);
		}
		else if ((*tok)->content_size == OREDIR)
		{
			ft_lstaddback(&new_node->args, ft_lstnew((*tok)->content,
						ft_strlen((*tok)->content) + 1));
			if (eat(tok, OREDIR))
				return (NULL);
			ft_lstaddback(&new_node->args, ft_lstnew((*tok)->content,
						ft_strlen((*tok)->content) + 1));
			if (eat(tok, WORD))
				return (NULL);
		}
	}
	return (new_node);
}

void	execute(t_ast *tree)
{
	if (!tree)
		return ;
	ft_putnbr(tree->type);
	ft_putchar('\n');
	/* ft_putlst(tree->args); */
	/* ft_putlst(tree->redir); */
	execute(tree->left);
	execute(tree->right);
}

int		parser(t_list *tok)
{
	t_ast	*tree;
	tree = job(&tok);
	if (tok && tok->content_size != END)
		parsing_error(tok->content);
	else
		execute(tree);
	return (1);
}
