/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:05:29 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/07 17:47:19 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

static void	print_name(const char *str)
{
	const char	*tmp;

	tmp = str;
	while (*tmp)
		tmp++;
	write(STDOUT_FILENO, " > ", 3);
	write(STDOUT_FILENO, str, tmp - str);
	write(STDOUT_FILENO, " : ", 3);
}

static void	print_nbr(int nbr)
{
	unsigned int	a;
	char			c;

	a = nbr;
	if (nbr < 0)
	{
		write(STDOUT_FILENO, "-", 1);
		a = -nbr;
	}
	if (a > 9)
	{
		print_nbr(a / 10);
		print_nbr(a % 10);
	}
	else
	{
		c = a + '0';
		write(STDOUT_FILENO, &c, 1);
	}
}

static int	print_final(int	total, int fail)
{
	write(STDOUT_FILENO, "\nSuccessful tests: ", 19);
	print_nbr(total - fail);
	write(STDOUT_FILENO, "/", 1);
	print_nbr(total);
	write(STDOUT_FILENO, "\n", 1);
	return (fail ? -1 : 0);
}

int			launch_tests(t_unit_test *list)
{
	int		total;
	int		fail;

	total = 0;
	fail = 0;
	while (list)
	{
		print_name(list->name);
		if ((list->status = run_unit_test(list->func)))
			fail++;
		total++;
		list = list->next;
	}
	return (print_final(total, fail));
}
