/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_pipe_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:03:05 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/11 10:01:28 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"
#include "libunit.h"
#include "libft.h"

int		pipe_one(void)
{
	int		pfd[2];
	int		in_fd;
	int		ret;
	char	str[1000];

	pipe(pfd);
	in_fd = dup(STDOUT_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	system("../parsing < pipe_command/01_input");
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
