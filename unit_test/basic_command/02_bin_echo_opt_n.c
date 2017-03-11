/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_bin_echo_opt_n.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 16:49:45 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/11 12:50:04 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"
#include "libunit.h"
#include "libft.h"

int		bin_echo_opt_n(void)
{
	if (!check_stdout("basic_command/02_input", "mdr"))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
