/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 10:18:37 by hdelaby           #+#    #+#             */
/*   Updated: 2017/01/27 10:20:03 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**get_global_env(t_list **env)
{
	static t_list	**lst;

	if (env)
		lst = env;
	return (lst);
}

int		get_exit_status(int status)
{
	static int	old_status = 0;

	if (status != -1)
		old_status = status;
	return (old_status);
}
