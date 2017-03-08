/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_unit_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:11:59 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/07 17:45:33 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"

static int	print_status(int status)
{
	if (status == 0)
		write(STDOUT_FILENO, "[OK]\n", 5);
	else if (status == SIGSEGV)
		write(STDOUT_FILENO, "[SEGV]\n", 7);
	else if (status == SIGBUS)
		write(STDOUT_FILENO, "[BUS]\n", 6);
	else if (status == SIGABRT)
		write(STDOUT_FILENO, "[ABRT]\n", 7);
	else
		write(STDOUT_FILENO, "[FAIL]\n", 7);
	return (status);
}

int			run_unit_test(int (*func)(void))
{
	pid_t	child;
	int		ret;
	int		status;

	ret = 0;
	child = fork();
	if (child == -1)
	{
		write(STDERR_FILENO, "Fork error\n", 11);
		return (-1);
	}
	else if (child == 0)
		exit(func());
	wait(&status);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ret = WTERMSIG(status);
	return (print_status(ret));
}
