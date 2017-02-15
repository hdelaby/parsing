/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 15:26:23 by hdelaby           #+#    #+#             */
/*   Updated: 2017/01/26 16:28:53 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd_get_arg(char *arg, t_list **env)
{
	char	*path;

	if (!arg && !ft_getenv("HOME", env))
	{
		ft_putendl("cd: HOME not set");
		return (NULL);
	}
	else if (!arg)
		path = ft_getenv("HOME", env);
	else if (!ft_strcmp(arg, "-"))
	{
		path = ft_getenv("OLDPWD", env);
		if (!path)
			ft_putendl("cd: OLDPWD not set");
	}
	else
		path = arg;
	return (path);
}

static char	*cd_get_fullpath(char *dir, t_list **env)
{
	char	*fullpath;

	if (dir && dir[0] != '/')
	{
		if ((dir = ft_getenv("PWD", env)))
		{
			dir = ft_strjoin(dir, "/");
			fullpath = ft_strjoin(dir, fullpath);
			free(dir);
		}
		else
			return (NULL);
	}
	else
		fullpath = ft_strdup(dir);
	return (fullpath);
}

int			cd_chg_env(char *path, t_list **env, int has_opt)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (has_opt && !chdir(path))
	{
		ft_setenv("OLDPWD", buf, 1, env);
		free(buf);
		buf = NULL;
		buf = getcwd(buf, 0);
		ft_setenv("PWD", buf, 1, env);
	}
	else if (!chdir(path))
	{
		if (ft_getenv("PWD", env))
			ft_setenv("OLDPWD", ft_getenv("PWD", env), 1, env);
		ft_setenv("PWD", path, 1, env);
	}
	else
	{
		free(buf);
		return (1);
	}
	free(buf);
	return (0);
}

int			cd_path_errors(char **fullpath, char *dir, int has_opt, char *arg)
{
	if (!access(has_opt ? dir : *fullpath, F_OK))
		ft_puterr("cd", E_ACCES, arg, 1);
	else
		ft_puterr("cd", E_NOENT, arg, 1);
	ft_strdel(fullpath);
	return (1);
}

int			bi_cd(char **args, t_list **env)
{
	char	*fullpath;
	char	*dir;
	int		has_opt;

	has_opt = 0;
	args += 1;
	while (*args && *args[0] == '-')
		if (cd_get_option(*(args++), &has_opt))
		{
			args--;
			break ;
		}
	if (!(dir = cd_get_arg(*args, env))
			|| !(fullpath = cd_get_fullpath(dir, env)))
		return (1);
	ft_canon_path(&fullpath);
	if (cd_chg_env(has_opt ? dir : fullpath, env, has_opt))
		return (cd_path_errors(&fullpath, dir, has_opt, *args));
	if (*args && !ft_strcmp(*args, "-"))
		ft_putendl(ft_getenv("PWD", env));
	free(fullpath);
	return (0);
}
