/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 13:37:06 by hdelaby           #+#    #+#             */
/*   Updated: 2017/02/28 13:39:06 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include "libft.h"

typedef struct	s_ast
{
	char			*content;
	int				type;
	struct s_ast	*right;
	struct s_ast	*left;
}				t_ast;

#endif
