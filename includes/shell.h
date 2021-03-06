/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 11:28:34 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/30 11:15:01 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

typedef struct	s_sh
{
	int		status;
	t_dlist	*hist;
	t_list	*heredoc;
	char	**env;
}				t_sh;

#endif
