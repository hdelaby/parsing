/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:55:27 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/30 16:10:56 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "line_edition.h"

/* char	*replace_backslash(char *str) */
/* { */
/* 	char	*tmp; */
/* 	char	*ret; */
/* 	int		count; */
/* 	int		i; */

/* 	tmp = str; */
/* 	ret = str; */
/* 	count = 0; */
/* 	i = 0; */
/* 	while (*ret) */
/* 		if (*(ret++) == '\n') */
/* 			count++; */
/* 	tmp = str; */
/* 	if (!(ret = (char *)malloc(sizeof(char) * ft_strlen(str) + count + 1))) */
/* 		return (NULL); */
/* 	while (*tmp) */
/* 	{ */
/* 		if (*tmp == '\n') */
/* 			ret[i++] = '\\'; */
/* 		ret[i++] = *(tmp++); */
/* 	} */
/* 	ret[i++] = '\0'; */
/* 	free(str); */
/* 	return (ret); */
/* } */

int		complete_cmd(t_token *tok, char *prompt)
{
	size_t	len;
	char	*input;

	len = ft_strlen(tok->ptr_for_free);
	ft_putstr_fd(prompt, 2);
	if (!(input = ft_strjoin(tok->ptr_for_free, "\n")))
		return (EXIT_FAILURE);
	free(tok->ptr_for_free);
	tok->ptr_for_free = input;
	if (!(input = line_editing(tok->hist))
			|| !(tok->cmd = ft_strfreejoin(tok->ptr_for_free, input)))
		return (EXIT_FAILURE);
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
