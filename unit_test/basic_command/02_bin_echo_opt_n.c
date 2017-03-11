/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_bin_echo_opt_n.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 16:49:45 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/11 10:00:40 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"
#include "libunit.h"
#include "libft.h"

int		bin_echo_opt_n(void)
{
	int		pfd[2];
	int		in_fd;
	int		ret;
	char	str[1000];

	pipe(pfd);
	in_fd = dup(STDOUT_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	system("../parsing < basic_command/02_input");
	ret = read(pfd[0], &str, 1000);
	str[ret] = '\0';
	close(pfd[0]);
	close(pfd[1]);
	dup2(in_fd, STDOUT_FILENO);
	close(in_fd);
	if (!ft_strcmp(str, "mdr"))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
