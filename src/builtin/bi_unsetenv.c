/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:00:37 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/22 16:00:51 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int		bi_unsetenv(char **args, char ***env)
{
	if (args[1] == NULL)
	{
		ft_putendl("Usage:\nunsetenv [key ...]");
		return (-1);
	}
	args = args + 1;
	while (*args)
		ft_unsetenv(*(args++), env);
	return (0);
}
