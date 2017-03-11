/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_pipe_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 15:41:12 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/11 15:53:06 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"

int		pipe_two(void)
{
	if (!check_stdout("pipe_command/02_input", "       1\n"))
			return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
