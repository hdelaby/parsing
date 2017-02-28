/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 13:42:30 by hdelaby           #+#    #+#             */
/*   Updated: 2017/02/28 16:40:27 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ast.h"

t_ast	*ast_node(int type, t_ast *left, t_ast *right)
{
	t_ast	*newnode;

	newnode = (t_ast *)malloc(sizeof(t_ast));
	if (!newnode)
		return (NULL);
	ft_bzero(newnode, sizeof(t_ast));
	newnode->type = type;
	newnode->left = left;
	newnode->right = right;
	return (newnode);
}

t_ast	*ast_leaf(int type)
{
	t_ast	*newnode;

	newnode = (t_ast *)malloc(sizeof(t_ast));
	if (!newnode)
		return (NULL);
	ft_bzero(newnode, sizeof(t_ast));
	newnode->type = type;
	return (newnode);
}
