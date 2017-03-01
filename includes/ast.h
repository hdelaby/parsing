/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 13:37:06 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/01 09:12:50 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "libft.h"

# define ARG_NODE	1
# define PIPE_NODE	2
# define SEQ_NODE	3

typedef struct	s_ast
{
	int				type;
	t_list			*args;
	t_list			*redir;
	struct s_ast	*right;
	struct s_ast	*left;
}				t_ast;

t_ast	*ast_node(int type, t_ast *left, t_ast *right);
t_ast	*ast_leaf(int type);

#endif
