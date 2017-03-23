/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:48:20 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/23 14:08:22 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "signal_handling.h"

/*
** This set of functions need to evolve to cover all cases of tree
** architecture. Right now it is unclear what functions are doing.
*/

void	apply_redir(t_list *lst)
{
	if (lst)
		get_redir(lst);
}

void	run_pipe(t_ast *tree, int in_fd, t_sh *sh)
{
	int		pdes[2];
	int		save_out;
	pid_t	child;

	pipe(pdes);
	child = fork();
	if ((int)child == -1)
		return ;
	else if ((int)child == 0)
	{
		close(pdes[WRITE_END]);
		if (tree->right->type == PIPE_NODE)
			run_pipe(tree->right, pdes[READ_END], sh);
		else
		{
			dup2(pdes[READ_END], STDIN_FILENO);
			execute_cmd(tree->right, sh);
		}
		exit(sh->status);
	}
	else
	{
		close(pdes[READ_END]);
		save_out = dup(STDOUT_FILENO);
		dup2(in_fd, STDIN_FILENO);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		execute_cmd(tree->left, sh);
		dup2(save_out, STDOUT_FILENO);
		close(save_out);
		close(pdes[READ_END]);
	}
}

void	handle_pipe_node(t_ast *tree, t_sh *sh)
{
	int		fd_stdin;
	pid_t	child;
	int		status;

	if (!tree)
		return ;
	if (tree->type != PIPE_NODE)
		return (execute_cmd_bis(tree, sh));
	child = fork();
	if ((int)child == -1)
		return ;
	else if ((int)child == 0)
	{
		fd_stdin = dup(STDIN_FILENO);
		run_pipe(tree, STDIN_FILENO, sh);
		dup2(fd_stdin, STDIN_FILENO);
		close(fd_stdin);
	}
	wait(&status);
	sh->status = get_status(status);
}

void	execute(t_ast *tree, t_sh *sh)
{
	signal(SIGINT, &parent_sigint_handler);
	if (!tree)
		return ;
	if (tree->type == SEQ_NODE)
	{
		handle_pipe_node(tree->left, sh);
		execute(tree->right, sh);
	}
	else
		handle_pipe_node(tree, sh);
}
