/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:02:07 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/22 15:37:51 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "parser.h"

static char		**find_env_entry(const char *name, char **env)
{
	size_t	name_len;
	size_t	env_len;

	if (!name || !*name || !env)
		return (NULL);
	name_len = ft_strlen(name);
	while (*env)
	{
		env_len = (size_t)(ft_strchr(*env, '=') - *env);
		if (env_len == name_len &&!ft_strncmp(*env, name, name_len))
			return (&(*env));
		env++;
	}
	return (NULL);
}

char			*ft_getenv(const char *name, char **env)
{
	char	*entry;

	entry = NULL;
	if (!env || !*env || !name)
		return (NULL);
	if ((entry = *find_env_entry(name, env)))
		return (ft_strchr(entry, '=') + 1);
	return (NULL);
}

static char		*cat_newvar(const char *name, const char *value)
{
	char	*new_var;

	new_var = ft_strnew(ft_strlen(name) + ft_strlen(value) + 3);
	if (!new_var)
		return (NULL);
	new_var = ft_strcpy(new_var, name);
	new_var = ft_strcat(new_var, "=");
	new_var = ft_strcat(new_var, value);
	return (new_var);
}

int				ft_setenv(const char *name, const char *value, int overwrite,
		char ***env)
{
	char	*new_var;
	char	**entry;
	int		i;

	i = 0;
	entry = NULL;
	if (!name || ft_strchr(name, '=') || !ft_strlen(name) || !env)
		return (EXIT_FAILURE);
	if ((entry = find_env_entry(name, *env)))
	{
		if (!overwrite)
			return (EXIT_SUCCESS);
		new_var = cat_newvar(name, value);
		if (!new_var)
			return (EXIT_FAILURE);
		free(*entry);
		*entry = new_var;
	}
	else
	{
		new_var = cat_newvar(name, value);
		*env = ft_tabadd(*env, new_var);
		free(new_var);
	}
	return (EXIT_SUCCESS);
}

int				ft_unsetenv(const char *name, char ***env)
{
	char	**entry;

	if (!name || !ft_strlen(name) || !env ||
			!(entry = find_env_entry(name, *env)))
		return (EXIT_FAILURE);
	*env = ft_tabremove(*env, (size_t)(entry - *env));
	return (EXIT_SUCCESS);
}
