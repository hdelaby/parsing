/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_semico_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 12:55:41 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/11 12:58:13 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"

int		semico_one(void)
{
	if (!check_stdout("semi_command/01_input", "mdr\nmdr\n"))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
