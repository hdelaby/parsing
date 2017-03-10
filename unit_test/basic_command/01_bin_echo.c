/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_bin_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 16:35:08 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/10 16:47:54 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"
#include "libunit.h"
#include "libft.h"

int		bin_echo(void)
{
	int		pfd[2];
	int		in_fd;
	int		ret;
	char	str[1000];

	pipe(pfd);
	in_fd = dup(STDOUT_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	system("../parsing < basic_command/01_input");
	ret = read(pfd[0], &str, 1000);
	str[ret] = '\0';
	close(pfd[0]);
	close(pfd[1]);
	dup2(in_fd, STDOUT_FILENO);
	close(in_fd);
	if (!ft_strcmp(str, "mdr\n"))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
