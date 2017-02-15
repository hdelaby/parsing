/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:02:07 by hdelaby           #+#    #+#             */
/*   Updated: 2017/01/11 17:02:44 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*ft_getenv(const char *name, t_list **env)
{
	while (*env && !cmp_find_env((*env)->content, (char *)name))
		env = &(*env)->next;
	if (!(*env))
		return (NULL);
	return (ft_strchr((*env)->content, '=') + 1);
}

static char		*cat_newvar(const char *name, const char *value)
{
	char	*new_var;

	new_var = ft_strnew(ft_strlen(name) + ft_strlen(value) + 3);
	new_var = ft_strcpy(new_var, name);
	new_var = ft_strcat(new_var, "=");
	new_var = ft_strcat(new_var, value);
	return (new_var);
}

int				ft_setenv(const char *name, const char *value, int overwrite,
		t_list **env)
{
	char	*new_var;

	if (!name || !ft_strlen(name) || ft_strchr(name, '='))
		return (-1);
	if (ft_lstfind(*env, (void *)name, &cmp_find_env))
	{
		if (!overwrite)
			return (0);
		while (!cmp_find_env((*env)->content, (char *)name))
			env = &(*env)->next;
		new_var = cat_newvar(name, value);
		free((*env)->content);
		(*env)->content = new_var;
	}
	else
	{
		new_var = cat_newvar(name, value);
		ft_lstaddback(env, ft_lstnew(new_var, ft_strlen(new_var) + 1));
		free(new_var);
	}
	return (0);
}

static t_list	*ft_rem_env(t_list *lst, const char *name)
{
	t_list	*tmp;

	if (lst == NULL)
		return (NULL);
	if (ft_strstr(lst->content, name))
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		return (tmp);
	}
	lst->next = ft_rem_env(lst->next, name);
	return (lst);
}

int				ft_unsetenv(const char *name, t_list **env)
{
	if (!name || !ft_strlen(name) || ft_strchr(name, '='))
		return (-1);
	*env = ft_rem_env(*env, name);
	return (0);
}
