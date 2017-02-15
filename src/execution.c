/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 18:05:41 by hdelaby           #+#    #+#             */
/*   Updated: 2017/01/27 10:10:04 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	apply_builtin(char *cmd, char **args, t_list **env)
{
	static t_builtin	tab[] = {
		{"echo", &bi_echo},
		{"env", &bi_env},
		{"setenv", &bi_setenv},
		{"unsetenv", &bi_unsetenv},
		{"exit", &bi_exit},
		{"cd", &bi_cd}
	};
	int					i;

	i = 0;
	while (i < 6)
	{
		if (!ft_strcmp(tab[i].cmd, cmd))
			return (tab[i].fct(args, env));
		i++;
	}
	return (-2);
}

static int	exec_errors(char *ptr, int flag)
{
	if (!access(ptr, F_OK) && access(ptr, X_OK))
		return (ft_puterr(E_ACCES, ptr, NULL, 1));
	else if (access(ptr, F_OK) && flag)
		return (ft_puterr(E_NOCMD, ptr, NULL, 1));
	return (0);
}

/*
** According to POSIX, if the command contains a '/' then assume it is a path
** to be tried directly with execve.
** Error message printed if the executable cannot be executed.
*/

static int	my_execve(char *cmd, char **args, char **env, t_list **lst_env)
{
	char	**tab_path;
	char	*ptr;
	int		i;

	i = 0;
	ptr = ft_getenv("PATH", lst_env);
	if (!ft_strchr(cmd, '/'))
	{
		tab_path = ft_strsplit(ptr ? ptr : DEFAULT_PATH, ':');
		while (tab_path[i])
		{
			ptr = ft_build_path(tab_path[i], cmd);
			if (!exec_errors(ptr, 0))
				execve(ptr, args, env);
			ptr ? free(ptr) : ft_putstr("");
			i++;
		}
		return (get_exit_status(ft_puterr(E_NOCMD, cmd, NULL, 1)));
	}
	else
	{
		if (!exec_errors(cmd, 1))
			execve(cmd, args, env);
	}
	return (get_exit_status(1));
}

int			exec_home(char *cmd, char **args, t_list **env)
{
	int		ret;

	signal(SIGINT, &child_sigint_handler);
	if ((ret = apply_builtin(cmd, args, env)) != -2)
		return (get_exit_status(ret));
	return (get_exit_status(apply_bin(cmd, args, env)));
}

int			apply_bin(char *cmd, char **args, t_list **env)
{
	pid_t	pid;
	char	**tab_env;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		tab_env = ft_lst_to_tab(*env);
		my_execve(cmd, args, tab_env, env);
		ft_tabdel(tab_env);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (status == 2)
			ft_putendl("\nInterruption of process");
	}
	return (status);
}
