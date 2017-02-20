/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 11:13:11 by hdelaby           #+#    #+#             */
/*   Updated: 2017/02/20 17:02:47 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handle_other(t_token *tok, t_list **tokens_lst, char key)
{
	if (tok->is_pipe || tok->is_iredir || tok->is_oredir)
		end_token(tok, tokens_lst);
		tok->str[tok->str_i++] = key;
}

void	handle_oredir(t_token *tok, t_list **tokens_lst)
{
	if (tok->is_quoted)
		tok->str[tok->str_i++] = '>';
	else
	{
		end_token(tok, tokens_lst);
		tok->str[tok->str_i++] = '>';
		tok->is_oredir = 1;
	}
}

void	handle_iredir(t_token *tok, t_list **tokens_lst)
{
	if (tok->is_quoted)
		tok->str[tok->str_i++] = '<';
	else
	{
		end_token(tok, tokens_lst);
		tok->str[tok->str_i++] = '<';
		tok->is_iredir = 1;
	}
}

void	handle_pipe(t_token *tok, t_list **tokens_lst)
{
	if (tok->is_quoted)
		tok->str[tok->str_i++] = '|';
	else
	{
		end_token(tok, tokens_lst);
		tok->str[tok->str_i++] = '|';
		tok->is_pipe = 1;
	}
}

void	handle_space(t_token *tok, t_list **tokens_lst)
{
	if (tok->is_quoted)
		tok->str[tok->str_i++] = ' ';
	else
		end_token(tok, tokens_lst);
}

void	handle_dquote(t_token *tok, t_list **tokens_lst)
{
	(void)tokens_lst;
	if (tok->is_quoted)
		tok->is_quoted = 0;
	else
		tok->is_quoted = 1;
}
