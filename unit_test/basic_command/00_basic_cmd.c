/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_basic_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 11:47:00 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/08 16:22:52 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"
#include "libunit.h"
#include "libft.h"

int		test(void)
{
	int		pfd[2];
	int		in_fd;
	int		ret;
	char	str[1000];

	pipe(pfd);
	in_fd = dup(STDOUT_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	system("../parsing < basic_command/in_test");
	ret = read(pfd[0], &str, 1000);
	str[ret] = '\0';
	close(pfd[0]);
	close(pfd[1]);
	dup2(in_fd, STDOUT_FILENO);
	close(in_fd);
	return (EXIT_SUCCESS);
}

int		basic_cmd(void)
{
	t_unit_test	*lst;

	lst = NULL;
	ft_putendl("Basic command");
	load_test(&lst, "Basic test", &test);
	return (launch_tests(lst));
}
