/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 11:13:11 by hdelaby           #+#    #+#             */
/*   Updated: 2017/02/22 11:44:14 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
** ACCEPTED SYNTAX
** [n]< word
** [n]> word
** [n]<< word
** [n]>> word
** [n]<& word
** [n]>& word
** [n]<> word
*/

void	handle_oredir(t_token *tok, t_list **lst)
{
	if (tok->type != DIGIT)
		end_token(tok, lst);
	tok->type = OREDIR;
	tok->str[tok->index++] = '>';
	if (*tok->cmd == '>')
		tok->str[tok->index++] = *tok->cmd++;
	else if (*tok->cmd == '&')
		tok->str[tok->index++] = *tok->cmd++;
	end_token(tok, lst);
}

void	handle_iredir(t_token *tok, t_list **lst)
{
	if (tok->type != DIGIT)
		end_token(tok, lst);
	tok->type = IREDIR;
	tok->str[tok->index++] = '<';
	if (*tok->cmd == '>')
		tok->str[tok->index++] = *tok->cmd++;
	else if (*tok->cmd == '<')
		tok->str[tok->index++] = *tok->cmd++;
	else if (*tok->cmd == '&')
		tok->str[tok->index++] = *tok->cmd++;
	end_token(tok, lst);
}

void	handle_pipe(t_token *tok, t_list **lst)
{
		end_token(tok, lst);
		tok->str[tok->index++] = '|';
		tok->type = PIPE;
		end_token(tok, lst);
}
