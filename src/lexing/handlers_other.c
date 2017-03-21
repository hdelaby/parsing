/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 11:32:05 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/21 08:50:46 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "line_edition.h"

void	handle_quote(t_token *tok, t_list **lst)
{
	(void)lst;
	tok->type = WORD;
	while (*tok->cmd != '\'')
		tok->str[tok->index++] = *tok->cmd++;
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
	while (*tok->cmd && *tok->cmd != '\"')
		tok->str[tok->index++] = *tok->cmd++;
	if (!*tok->cmd)
		line_editing();
	tok->cmd++;
}
