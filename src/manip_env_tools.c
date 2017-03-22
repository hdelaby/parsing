/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 15:08:14 by hdelaby           #+#    #+#             */
/*   Updated: 2017/01/11 16:42:20 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmp_find_env(char *content, char *env_var)
{
	if (!ft_strncmp(content, env_var, ft_strlen(env_var))
			&& content[ft_strlen(env_var)] == '=')
		return (1);
	return (0);
}
