/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:36:40 by hdelaby           #+#    #+#             */
/*   Updated: 2017/01/14 15:13:24 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

void	child_sigint_handler(int signum)
{
	signal(signum, &child_sigint_handler);
}

void	parent_sigint_handler(int signum)
{
	signal(signum, &parent_sigint_handler);
	ft_putchar('\n');
	put_prompt(get_global_env(NULL));
}
