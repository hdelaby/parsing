/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 10:31:50 by hdelaby           #+#    #+#             */
/*   Updated: 2017/01/27 10:23:22 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*(str++)))
			return (0);
	}
	return (1);
}

int			bi_exit(char **args, t_list **env)
{
	int		ret;

	(void)env;
	if (args[1])
	{
		if (args[2])
			return (ft_puterr("exit", "Too many arguments", NULL, 1));
		if (!is_number(args[1]))
			exit(ft_puterr("exit", "Numeric argument required", NULL, 255));
		exit(ft_atoi(args[1]));
	}
	else
		ret = get_exit_status(-1);
	exit(ret);
}
