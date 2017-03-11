/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_semico_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 12:54:17 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/11 15:48:57 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"

int		semico_cmd(void)
{
	t_unit_test *lst;

	lst = NULL;
	ft_putendl("Semicolon command");
	load_test(&lst, "Semico 1", &semico_one);
	load_test(&lst, "Semico 2", &semico_two);
	return (launch_tests(lst));
}
