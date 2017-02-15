/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:20:46 by hdelaby           #+#    #+#             */
/*   Updated: 2017/01/28 16:18:13 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static int	get_default_env(t_list **env)
{
	char	*tmp;
	char	*buf;
	int		ret;

	ret = 0;
	buf = NULL;
	buf = getcwd(buf, 0);
	tmp = ft_strjoin("/Users/", getlogin());
	if (ft_setenv("LOGNAME", getlogin(), 0, env)
		|| ft_setenv("HOME", tmp, 0, env)
		|| ft_setenv("PATH", DEFAULT_PATH, 0, env)
		|| ft_setenv("TERM", "dumb", 0, env)
		|| ft_setenv("PWD", buf, 0, env))
		ret = 1;
	free(tmp);
	free(buf);
	return (ret);
}

static int	indiv_cmd(t_list **env, char **cmd_tokens)
{
	int		i;
	char	**args;

	if (!cmd_tokens || !env)
		exit(get_exit_status(-1));
	i = 0;
	while (cmd_tokens[i])
	{
		args = cmd_parsing(cmd_tokens + i++);
		if (args != NULL)
		{
			exec_home(args[0], args, env);
			ft_tabdel(args);
		}
		else
			return (-1);
	}
	return (0);
}

static int	shell_loop(t_list **env)
{
	char	*str;
	char	**args;
	char	**test;
	int		i;

	i = 0;
	signal(SIGINT, &parent_sigint_handler);
	while (42)
	{
		str = NULL;
		args = NULL;
		put_prompt(env);
		get_next_line(0, &str);
		test = input_token(str);
		indiv_cmd(env, test);
		free(test);
		signal(SIGINT, &parent_sigint_handler);
	}
}

int			main(int ac, char **av, char **env)
{
	t_list *lst;

	(void)ac;
	(void)av;
	lst = ft_tab_to_lst(env);
	get_default_env(&lst);
	if (!lst)
		return (1);
	get_global_env(&lst);
	shell_loop(&lst);
	return (0);
}
