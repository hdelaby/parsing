/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 11:46:05 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/07 15:11:49 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

int		load_test(t_unit_test **list, const char *name, int (*func)(void))
{
	t_unit_test	*new;

	new = (t_unit_test *)malloc(sizeof(t_unit_test));
	if (!new)
		return (EXIT_FAILURE);
	new->name = name;
	new->func = func;
	new->status = -255;
	new->next = NULL;
	while (*list)
		list = &(*list)->next;
	*list = new;
	return (EXIT_SUCCESS);
}
