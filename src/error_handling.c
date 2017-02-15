/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:32:21 by hdelaby           #+#    #+#             */
/*   Updated: 2017/01/14 14:46:06 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_error.h"

int		ft_puterr(char *program, char *errmsg, char *arg, int error_code)
{
	ft_putstr_fd(program, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(errmsg, 2);
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(arg, 2);
	}
	else
		ft_putchar_fd('\n', 2);
	return (error_code);
}
