/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 18:03:01 by hdelaby           #+#    #+#             */
/*   Updated: 2017/01/27 09:25:07 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_cwd_only(char *path)
{
	if (ft_strchr(path, '/') == ft_strrchr(path, '/'))
		return (ft_strrchr(path, '/'));
	else
		return (ft_strrchr(path, '/') + 1);
}

void		put_prompt(t_list **env)
{
	char	*cwd;
	int		flag;

	flag = 0;
	cwd = NULL;
	if (!env || !(cwd = ft_getenv("PWD", env)))
	{
		flag = 1;
		cwd = getcwd(cwd, 0);
	}
	ft_putstr_fd(F_BLU, 0);
	ft_putstr_fd(extract_cwd_only(cwd), 0);
	ft_putstr_fd(RESET, 0);
	ft_putstr_fd(" $> ", 0);
	if (flag)
		free(cwd);
}
