/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_semico_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 15:47:54 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/11 15:48:00 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"

int		semico_two(void)
{
	if (!check_stdout("semi_command/02_input", "mdr\nmdr\nmdr\n"))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
