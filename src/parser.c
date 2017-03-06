/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 08:58:46 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/06 13:48:05 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ast.h"

t_ast	*list(t_list **tok, int *status);
t_ast	*job(t_list **tok, int *status);
int		eat(t_list **tok, int type, int *status);

int		is_arg_tok(t_list *tok)
{
	if (tok->content_size == WORD || tok->content_size == IREDIR ||
			tok->content_size == OREDIR)
		return (1);
	return (0);
}

void	linebreak(t_list **tok, int *status)
{
	while ((*tok)->content_size == EOL)
		eat(tok, EOL, status);
}

void	parsing_error(char *str)
{
	ft_putstr_fd("Parsing error at ", 2);
	ft_putendl_fd(str, 2);
}

int		eat(t_list **tok, int type, int *status)
{
	if ((*tok)->content_size == (size_t)type)
		*tok = (*tok)->next;
	else
	{
		*status = 1;
		return (1);
	}
	return (0);
}

t_ast	*command_line(t_list **tok, int *status)
{
	t_ast	*new_node;
	t_ast	*job_node;

	if ((job_node = job(tok, status)) && (*tok)->content_size == SEMICO)
	{
		if (eat(tok, SEMICO, status))
			return (NULL);
		if (!(new_node = ast_node(SEQ_NODE, job_node, NULL)))
			return (NULL);
		new_node->right = command_line(tok, status);
		return (new_node);
	}
	else if (job_node && (*tok)->content_size == EOL)
	{
		if (eat(tok, EOL, status))
			return (NULL);
		if (!(new_node = ast_node(SEQ_NODE, job_node, NULL)))
			return (NULL);
		new_node->right = command_line(tok, status);
		return (new_node);
	}
	return (job_node);
}

t_ast	*job(t_list	**tok, int *status)
{
	t_ast	*new_node;
	t_ast	*arg_list;

	if ((arg_list = list(tok, status)) && (*tok)->content_size == PIPE)
	{
		if (eat(tok, PIPE, status))
			return (NULL);
		if (!(new_node = ast_node(PIPE_NODE, arg_list, NULL)))
			return (NULL);
		linebreak(tok, status);
		new_node->right = job(tok, status);
		if (!new_node->right)
		{
			*status = 1;
			return (NULL);
		}
		return (new_node);
	}
	return (arg_list);
}

int		feed_redir(t_list **tok, int *status, t_ast **node, size_t type)
{
	t_list	*lnode;

	lnode = ft_lstnew((*tok)->content, ft_strlen((*tok)->content) + 1);
	if (!lnode)
		return (1);
	lnode->content_size = type;
	ft_lstaddback(&(*node)->redir, lnode);
	if (eat(tok, type, status))
		return (1);
	ft_lstaddback(&(*node)->redir, ft_lstnew((*tok)->content,
				ft_strlen((*tok)->content) + 1));
	if (eat(tok, WORD, status))
		return (1);
	return (0);
}

t_ast	*list(t_list **tok, int *status)
{
	t_ast	*new_node;

	if (!is_arg_tok(*tok) || !(new_node = ast_leaf(ARG_NODE)))
		return (NULL);
	while (is_arg_tok(*tok))
	{
		if ((*tok)->content_size == WORD)
		{
			ft_lstaddback(&new_node->args, ft_lstnew((*tok)->content,
						ft_strlen((*tok)->content) + 1));
			if (eat(tok, WORD, status))
				return (NULL);
		}
		else if ((*tok)->content_size == OREDIR)
		{
			if (feed_redir(tok, status, &new_node, OREDIR))
				return (NULL);
		}
		else if ((*tok)->content_size == IREDIR)
		{
			if (feed_redir(tok, status, &new_node, IREDIR))
				return (NULL);
		}
	}
	return (new_node);
}

t_ast	*parser(t_list *tok)
{
	t_ast	*tree;
	int		status;

	status = 0;
	tree = command_line(&tok, &status);
	if (status || tok->content_size != END)
	{
		parsing_error(tok->content);
		return (NULL);
	}
	return (tree);
}
