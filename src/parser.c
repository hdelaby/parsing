/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 08:58:46 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/01 09:21:32 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ast.h"

t_ast	*list(t_list **tok);
t_ast	*job(t_list **tok);

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

t_ast	*command_line(t_list **tok)
{
	t_ast	*new_node;
	t_ast	*job_node;

	if ((job_node = job(tok)) && (*tok)->content_size == SEMICO)
	{
		if (eat(tok, SEMICO))
			return (NULL);
		if (!(new_node = ast_node(SEQ_NODE, job_node, NULL)))
			return (NULL);
		new_node->right = command_line(tok);
		return (new_node);
	}
	else if (job_node && (*tok)->content_size == EOL)
	{
		if (eat(tok, EOL))
			return (NULL);
		if (!(new_node = ast_node(SEQ_NODE, job_node, NULL)))
			return (NULL);
		new_node->right = command_line(tok);
		return (new_node);
	}
	return (job_node);
}

t_ast	*job(t_list	**tok)
{
	t_ast	*new_node;
	t_ast	*arg_list;

	if ((arg_list = list(tok)) && (*tok)->content_size == PIPE)
	{
		if (eat(tok, PIPE))
			return (NULL);
		if (!(new_node = ast_node(PIPE_NODE, arg_list, NULL)))
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
	if (tree->type == ARG_NODE)
	{
		ft_putlst(tree->args);
		ft_putlst(tree->redir);
	}
	else
	{
		ft_putnbr(tree->type);
		ft_putchar('\n');
	}
	execute(tree->left);
	execute(tree->right);
}

int		parser(t_list *tok)
{
	t_ast	*tree;
	tree = command_line(&tok);
	if (tok && tok->content_size != END)
		parsing_error(tok->content);
	else
		execute(tree);
	return (1);
}
