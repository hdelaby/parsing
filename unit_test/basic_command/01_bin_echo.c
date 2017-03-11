/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_bin_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 16:35:08 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/11 12:43:12 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"
#include "libunit.h"
#include "libft.h"

int		bin_echo(void)
{
	if (!check_stdout("basic_command/01_input", "mdr\n"))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
