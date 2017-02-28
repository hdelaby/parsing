/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 11:13:11 by hdelaby           #+#    #+#             */
/*   Updated: 2017/02/27 15:02:52 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include <string.h>

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

void	handle_eol(t_token *tok, t_list **lst)
{
	char	*eol = "newline";
	end_token(tok, lst);
	tok->type = EOL;
	while (eol[tok->index])
	{
		tok->str[tok->index] = eol[tok->index];
		tok->index++;	
	}
	end_token(tok, lst);
}

void	handle_semicolon(t_token *tok, t_list **lst)
{
	end_token(tok, lst);
	tok->type = SEMICO;
	tok->str[tok->index++] = ';';
	end_token(tok, lst);
}

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
