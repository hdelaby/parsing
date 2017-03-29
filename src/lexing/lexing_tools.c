/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:55:27 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/29 12:05:54 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "line_edition.h"

int		complete_cmd(t_token *tok, char *prompt, int eol)
{
	size_t	len;
	char	*input;

	len = ft_strlen(tok->ptr_for_free);
	ft_putstr_fd(prompt, 2);
	if (eol)
	{
		if (!(input = ft_strjoin(tok->ptr_for_free, "\n")))
			return (EXIT_FAILURE);
		free(tok->ptr_for_free);
		tok->ptr_for_free = input;
	}
	if (!(input = line_editing(tok->hist)))
		return (EXIT_FAILURE);
	tok->cmd = ft_strjoin(tok->ptr_for_free, input);
	free(tok->ptr_for_free);
	tok->ptr_for_free = tok->cmd;
	tok->cmd += len;
	*(tok->hist) = ft_dlstgethead(*(tok->hist));
	free((*tok->hist)->content);
	if (!(input = ft_strdup(tok->ptr_for_free)))
		return (EXIT_FAILURE);
	(*tok->hist)->content = input;
	return (EXIT_SUCCESS);
}

int		is_line_empty(char *str)
{
	while (*str)
	{
		if (*(str++) != 32)
			return (0);
	}
	return (1);
}
