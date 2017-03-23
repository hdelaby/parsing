/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:48:20 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/23 09:49:40 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "signal_handling.h"

/*
** This set of functions need to evolve to cover all cases of tree
** architecture. Right now it is unclear what functions are doing.
** Also need to insert builtin etc.
*/

void	apply_redir(t_list *lst)
{
	if (lst)
		get_redir(lst);
}

void	run_pipe(t_ast *tree, int in_fd, t_sh *sh)
{
	int		pdes[2];
	pid_t	child;
	int		status;

	pipe(pdes);
	child = fork();
	if ((int)child == -1)
		return ;
	else if ((int)child == 0)
	{
		close(pdes[READ_END]);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		execute_cmd(tree->left, sh);
		exit(sh->status);
	}
	close(pdes[WRITE_END]);
	wait(&status);
	sh->status = get_status(status);
	if (tree->right->type == PIPE_NODE)
		run_pipe(tree->right, pdes[READ_END], sh);
	else
	{
		dup2(pdes[READ_END], STDIN_FILENO);
		execute_cmd(tree->right, sh);
		close(pdes[READ_END]);
	}
}

void	handle_pipe_node(t_ast *tree, t_sh *sh)
{
	int		fd_stdin;

	if (!tree)
		return ;
	fd_stdin = dup(STDIN_FILENO);
	if (tree->type != PIPE_NODE)
		return (execute_cmd(tree, sh));
	run_pipe(tree, STDIN_FILENO, sh);
	dup2(fd_stdin, STDIN_FILENO);
	close(fd_stdin);
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
