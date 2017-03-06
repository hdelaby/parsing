/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:42:31 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/06 14:58:16 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_REDIR_H
# define EXEC_REDIR_H

# include "execution.h"

# define REDIR_APD	1
# define REDIR_AMP	2
# define REDIR_RDWR	3

# define ARG_CLOSE	1
# define ARG_NUMBER	2
# define ARG_WORD	3

# define RDWR	O_RDWR | O_TRUNC | O_CREAT
# define RD		O_RDONLY | O_CREAT
# define WR		O_WRONLY | O_TRUNC | O_CREAT
# define WRAPD	O_WRONLY | O_APPEND | O_CREAT

struct	s_redir
{
	int		fd_dst;
	int		redir_type;
	int		fd_src;
	int		arg_type;
	char	*word;
};

void	get_redir(t_list *redir);

#endif
