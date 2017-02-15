/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 10:49:18 by hdelaby           #+#    #+#             */
/*   Updated: 2017/01/28 16:20:08 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**input_token(char *str)
{
	char	**test;

	test = ft_strsplit(str, ';');
	free(str);
	return (test);
}

char	**cmd_parsing(char **str)
{
	char	*input;
	char	**tab;

	input = ft_strtrim(*str);
	ft_strdel(str);
	if (!input)
		return (NULL);
	else if (*input == '\0')
	{
		free(input);
		return (NULL);
	}
	tab = ft_strsplit(input, ' ');
	free(input);
	return (tab);
}
