/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 09:21:04 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/26 10:37:23 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handling.h"
#include "libft.h"

void	parent_sigint_handler(int signum)
{
	signal(signum, &parent_sigint_handler);
	ft_putchar_fd('\n', 0);
}
