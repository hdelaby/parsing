/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_basic_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 11:47:00 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/10 17:01:40 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"
#include "libunit.h"
#include "libft.h"

int		basic_cmd(void)
{
	t_unit_test	*lst;

	lst = NULL;
	ft_putendl("Basic command");
	load_test(&lst, "Bin echo", &bin_echo);
	load_test(&lst, "Bin echo option n", &bin_echo_opt_n);
	return (launch_tests(lst));
}
