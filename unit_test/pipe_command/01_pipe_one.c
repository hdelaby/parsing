/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_pipe_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:03:05 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/11 12:49:49 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"
#include "libunit.h"
#include "libft.h"

int		pipe_one(void)
{
	if (!check_stdout("pipe_command/01_input", "mdr\n"))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
