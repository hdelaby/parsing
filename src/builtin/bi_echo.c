/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 15:26:39 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/23 10:15:00 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		bi_echo(char **args, char ***env)
{
	(void)env;
	args += 1;
	while (*args)
	{
		ft_putstr(*(args++));
		ft_putchar(' ');
	}
	ft_putchar('\n');
	return (0);
}
