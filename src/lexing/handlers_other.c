/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:32:05 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/30 16:11:22 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "line_edition.h"

void	handle_quote(t_token *tok, t_list **lst)
{
	(void)lst;
	tok->type = WORD;
	while (42)
	{
		if (*tok->cmd == '\'')
			break;
		if (*tok->cmd)
			tok->str[tok->index++] = *tok->cmd++;
		else
			complete_cmd(tok, "quote> ");
	}
	tok->cmd++;
}

void	handle_other(t_token *tok, t_list **lst, char key)
{
	(void)lst;
	if ((!tok->type || tok->type == DIGIT) && ft_isdigit(key))
		tok->type = DIGIT;
	else
		tok->type = WORD;
	tok->str[tok->index++] = key;
}

void	handle_space(t_token *tok, t_list **lst)
{
	end_token(tok, lst);
}

void	handle_dquote(t_token *tok, t_list **lst)
{
	(void)lst;
	tok->type = WORD;
	while (42)
	{
		if (*tok->cmd == '\"')
			break;
		if (*tok->cmd)
			tok->str[tok->index++] = *tok->cmd++;
		else
			complete_cmd(tok, "dquote> ");
	}
	tok->cmd++;
}
