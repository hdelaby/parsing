/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:48:20 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/09 15:16:32 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "exec_redir.h"

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

void	execute_cmd(t_ast *tree)
{
	//apply_redir(tree->redir);
	execve(tree->args[0], tree->args, NULL);
}

void	run_pipe(t_ast *tree, int in_fd)
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
		close(in_fd);
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		execute_cmd(tree->left);
		exit(1);
	}
	dup2(pdes[READ_END], STDIN_FILENO);
	close(pdes[WRITE_END]);
	wait(NULL);
	if (tree->right->type == PIPE_NODE)
		run_pipe(tree->right, pdes[READ_END]);
	else
	{
		execute_cmd(tree->right);
		close(pdes[READ_END]);
	}
}

void	handle_pipe_node(t_ast *tree)
{
	pid_t	child;

	if (!tree)
		return ;
	child = fork();
	if ((int)child == -1)
		return ;
	else if ((int)child == 0)
	{
		if (tree->type == PIPE_NODE)
			run_pipe(tree, STDIN_FILENO);
		else
			execute_cmd(tree);
	}
	wait(NULL);
}

void	execute(t_ast *tree)
{
	if (!tree)
		return ;
	if (tree->type == ARG_NODE)
		handle_pipe_node(tree);
	handle_pipe_node(tree->left);
	if (tree->right && tree->right->type == SEQ_NODE)
		execute(tree->right);
	else
		handle_pipe_node(tree->right);
}
