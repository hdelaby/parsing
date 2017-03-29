/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 11:13:11 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/29 11:53:00 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

#include "line_edition.h"

void	handle_pipe(t_token *tok, t_list **lst)
{
	end_token(tok, lst);
	tok->str[tok->index++] = '|';
	tok->type = PIPE;
	end_token(tok, lst);
	if (is_line_empty(tok->cmd))
		complete_cmd(tok, "pipe> ", 0);
}
