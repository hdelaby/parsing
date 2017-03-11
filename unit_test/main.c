/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 11:39:37 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/11 13:01:28 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include "unit_test.h"

int		main(void)
{
	int		ret;

	ret = 0;
	ret += basic_cmd();
	ft_putendl("_________________");
	ret += pipe_cmd();
	ft_putendl("_________________");
	ret += semico_cmd();
	return (ret);
}
