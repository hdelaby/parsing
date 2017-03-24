/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 09:51:49 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/24 16:50:23 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "signal_handling.h"
#include "builtin.h"

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

int		execute_builtin(t_ast *tree, t_sh *sh)
{
	int					i;
	static t_builtin	bi_tab[5] = {
		{"setenv", &bi_setenv},
		{"unsetenv", &bi_unsetenv},
		{"cd", &bi_cd},
		{"echo", &bi_echo},
		{"exit", &bi_exit}
	};

	i = 0;
	while (i < 5)
		if (!ft_strcmp(tree->args[0], bi_tab[i++].cmd))
			return (bi_tab[i - 1].fct(tree->args, &sh->env));
	return (-2);
}

void	execute_cmd(t_ast *tree, t_sh *sh)
{
	if ((sh->status = execute_builtin(tree, sh)) != -2)
		return ;
	my_execve(tree, sh);
}

void	execute_cmd_bis(t_ast *tree, t_sh *sh)
{
	int		status;
	pid_t	child;

	apply_redir(tree->redir);
	if ((sh->status = execute_builtin(tree, sh)) != -2)
		return ;
	child = fork();
	if ((int)child == 0)
		my_execve(tree, sh);
	wait(&status);
	sh->status = get_status(status);
}
