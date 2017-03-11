/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_pipe_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:00:14 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/11 15:48:43 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"
#include "libunit.h"
#include "libft.h"

int		pipe_cmd(void)
{
	t_unit_test *lst;

	lst = NULL;
	ft_putendl("Pipe command");
	load_test(&lst, "Pipe 1", &pipe_one);
	load_test(&lst, "Pipe 2", &pipe_two);
	return (launch_tests(lst));
}
