/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_framework.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 10:14:24 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/20 11:46:12 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_test.h"

int		check_stdout(char *path_to_input, char *expected_output)
{
	int		pfd[2];
	int		in_fd;
	int		ret;
	char	str[1000];
	(void)expected_output;

	pipe(pfd);
	in_fd = dup(STDOUT_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	ft_bzero(str, 1000);
	ft_strcpy(str, "../parsing < ");
	ft_strcat(str, path_to_input);
	system(str);
	ret = read(pfd[0], &str, 1000);
	if (ret == -1)
		return (1);
	str[ret] = '\0';
	close(pfd[0]);
	close(pfd[1]);
	dup2(in_fd, STDOUT_FILENO);
	close(in_fd);
	if (!ft_strcmp(str, expected_output))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
