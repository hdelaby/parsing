/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:29:51 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/28 10:15:50 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "libft.h"
#include <fcntl.h>

void	close_fds(void *content, size_t content_size)
{
	(void)content;
	close((int)content_size);
}

int		save_std_fd(int std_fd[3])
{
	if (((std_fd[0] = dup(STDIN_FILENO)) == -1)
			|| ((std_fd[1] = dup(STDOUT_FILENO)) == -1)
			|| ((std_fd[2] = dup(STDERR_FILENO)) == -1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		restore_std_fd(int std_fd[3])
{
	if (((dup2(std_fd[0], STDIN_FILENO) < 0) || close(std_fd[0]))
			|| ((dup2(std_fd[1], STDOUT_FILENO) < 0) || close(std_fd[1]))
			|| ((dup2(std_fd[2], STDERR_FILENO) < 0) || close(std_fd[2])))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
