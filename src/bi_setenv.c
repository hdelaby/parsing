/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 15:27:58 by hdelaby           #+#    #+#             */
/*   Updated: 2017/01/11 15:36:10 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		bi_setenv(char **args, t_list **env)
{
	size_t	tab_size;

	tab_size = ft_tablen(args);
	if (args[1] == NULL)
		ft_putlst(*env);
	else if (tab_size > 4)
	{
		ft_putendl("Usage:\nsetenv [key] [value [overwrite]]");
		return (-1);
	}
	else if (tab_size == 2)
		ft_setenv(args[1], "", 1, env);
	else if (tab_size == 3)
		ft_setenv(args[1], args[2], 1, env);
	else
		ft_setenv(args[1], args[2], ft_atoi(args[3]), env);
	return (0);
}
