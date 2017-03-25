/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 15:03:11 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/24 18:36:41 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "signal_handling.h"

void	exec_pipe(t_ast *tree, int in_fd, t_sh *sh)
{
	int		pdes[2];
	pid_t	child;

	pipe(pdes);
	child = fork();
	if ((int)child == -1)
		return ;
	else if ((int)child == 0)
	{
		close(pdes[READ_END]);
		dup2(in_fd, STDIN_FILENO);
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		exit(execute_cmd(tree->left, sh));
	}
	else
	{
	}
	exit(sh->status);
}

/*
** SAVE STDIN OUT ERR AND PUT THEM BACK AFTERWARDS
*/

void	pipe_node(t_ast *tree, t_sh *sh)
{
	int		fd_stdin;
	int		fd_stdout;
	pid_t	child;
	int		status;

	if (!tree)
		return ;
	if (tree->type != PIPE_NODE)
	{
		execute_cmd_bis(tree, sh);
		return ;
	}
	child = fork();
	if ((int)child == -1)
		return ;
	else if ((int)child == 0)
	{
		fd_stdin = dup(STDIN_FILENO);
		fd_stdout = dup(STDOUT_FILENO);
		exec_pipe(tree, STDIN_FILENO, sh);
		dup2(fd_stdin, STDIN_FILENO);
		dup2(fd_stdout, STDOUT_FILENO);
		close(fd_stdin);
		close(fd_stdout);
	}
	wait(&status);
	sh->status = get_status(status);
}
