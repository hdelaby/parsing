/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_pipe_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:00:14 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/10 17:02:13 by hdelaby          ###   ########.fr       */
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
	return (launch_tests(lst));
}
