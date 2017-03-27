/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:29:51 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/27 16:45:14 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "libft.h"
#include <fcntl.h>

int		close_fds(t_list *lst_fd)
{
	t_list	*tmp;

	tmp = NULL;
	while (lst_fd)
	{
		if (close((int)lst_fd->content))
			return (EXIT_FAILURE);
		tmp = lst_fd;
		lst_fd = lst_fd->next;
		free(tmp);
	}
	return (EXIT_SUCCESS);
}

int		save_std_fd(int std_fd[3])
{
	if (((std_fd[0] = dup(STDIN_FILENO)) == -1)
			|| ((std_fd[1] = dup(STDOUT_FILENO)) == -1)
			|| ((std_fd[2] = dup(STDERR_FILENO)) == -1))
		return (EXIT_FAILURE);
	if (close(STDIN_FILENO) || close(STDOUT_FILENO) || close(STDERR_FILENO))
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
