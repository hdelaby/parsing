/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 11:31:04 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/30 12:13:15 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "ast.h"
# include "lexer.h"

/*
** parser.c
*/

int		eat(t_list **tok, int type, int *status);
int		is_arg_tok(t_list *tok);
t_ast	*parser(t_list *tok);

/*
** grammar_elem.c
*/

t_ast   *command_line(t_list **tok, int *status);
t_ast   *job(t_list **tok, int *status);
t_ast   *list(t_list **tok, int *status);

#endif
