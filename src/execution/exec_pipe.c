/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 15:03:11 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/27 12:02:42 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "signal_handling.h"

static int	ret_value;

/*
** Main function behind pipe handling. Just need to be normed now.
** http://stackoverflow.com/questions/43030966/pipe-chaining-in-my-own-shell-implementation
*/

void	exec_pipe(t_ast *tree, t_sh *sh)
{
	int		pdes[2];
	pid_t	child_right;
	pid_t	child_left;

	pipe(pdes);
	if ((child_left = fork()) == -1)
		return ;
	else if (child_left == 0)
	{
		close(pdes[READ_END]);
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		exit(execute_cmd(tree->left, sh));
	}
	if ((child_right = fork()) == -1)
		return ;
	else if (child_right == 0)
	{
		close(pdes[WRITE_END]);
		dup2(pdes[READ_END], STDIN_FILENO);
		if (tree->right->type == PIPE_NODE)
			exec_pipe(tree->right, sh);
		else
		{
			ret_value = execute_cmd(tree->right, sh);
			exit(ret_value);
		}
	}
	close(pdes[WRITE_END]);
	close(pdes[READ_END]);
	wait(NULL);
	wait(NULL);
	exit(ret_value);
}

void	pipe_node(t_ast *tree, t_sh *sh)
{
	pid_t	child;
	int		status;

	if (!tree)
		return ;
	if (tree->type != PIPE_NODE)
	{
		sh->status = execute_cmd(tree, sh);
		return ;
	}
	child = fork();
	if (child == -1)
		return ;
	else if (child == 0)
		exec_pipe(tree, sh);
	else
	{
		wait(&status);
		sh->status = get_status(status);
		ft_putnbr(sh->status);
	}
}
