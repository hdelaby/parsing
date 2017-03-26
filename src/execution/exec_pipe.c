/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 15:03:11 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/26 17:49:38 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "signal_handling.h"

int		ret_val;

void	exec_pipe(t_ast *tree, t_sh *sh)
{
	int		pdes[2];
	pid_t	child;

	pipe(pdes);
	child = fork();
	if (child == -1)
		return ;
	else if (child == 0)
	{
		close(pdes[READ_END]);
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		execute_cmd(tree->left, sh);
		exit(0);
	}
	else
	{
		close(pdes[WRITE_END]);
		dup2(pdes[READ_END], STDIN_FILENO);
		if (tree->right->type == PIPE_NODE)
			exec_pipe(tree->right, sh);
		else
			ret_val = execute_cmd(tree->right, sh);
		exit(0);
	}
}

/*
** SAVE STDIN OUT ERR AND PUT THEM BACK AFTERWARDS
*/

void	pipe_node(t_ast *tree, t_sh *sh)
{
	pid_t	child;
	int		status;

	if (!tree)
		return ;
	child = fork();
	if (child == -1)
		return ;
	else if (child == 0)
		tree->type == PIPE_NODE ? exec_pipe(tree, sh) : execute_cmd(tree, sh);
	else
	{
		waitpid(child, &status, WNOHANG);
		sh->status = tree->type == PIPE_NODE ? ret_val : get_status(status);
	}
}
