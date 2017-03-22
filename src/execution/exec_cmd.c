/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 09:51:49 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/22 11:09:49 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "signal_handling.h"

int		get_status(int status)
{
	int		ret;

	ret = 0;
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ret = WTERMSIG(status);
	return (ret);
}

void	my_execve(t_ast *tree, t_sh *sh)
{
	char	*path;
	char	**tab_path;
	int		i;

	signal(SIGINT, SIG_DFL);
	i = 0;
	if (!ft_strchr(tree->args[0], '/'))
	{
		path = getenv("PATH");
		tab_path = ft_strsplit(path, ':');
		while (tab_path[i])
		{
			if (!(path = ft_build_path(tab_path[i], tree->args[0])))
				return ;
			execve(path, tree->args, sh->env);
			i++;
		}
	}
	else
		execve(tree->args[0], tree->args, sh->env);
	ft_putendl_fd("COMMAND NOT FOUND", 2);
	exit(1);
}

int		execute_builtin(t_ast *tree)
{
	if (!ft_strcmp(tree->args[0], "coucou"))
		return (EXIT_SUCCESS);
	return (-2);
}

void	execute_cmd(t_ast *tree, t_sh *sh)
{
	pid_t	child;
	int		status;

	if ((sh->status = execute_builtin(tree)) != -2)
		return ;
	child = fork();
	if ((int)child == -1)
		return ;
	else if ((int)child == 0)
		my_execve(tree, sh);
	wait(&status);
	sh->status = get_status(status);
}
