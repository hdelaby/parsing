/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:49:47 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/24 17:29:26 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"
# include "ast.h"
# include "shell.h"
# include <fcntl.h>

# define READ_END	0
# define WRITE_END	1

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

struct			s_redir
{
	int		fd_dst;
	int		redir_type;
	int		fd_src;
	int		arg_type;
	char	*word;
};

typedef struct	s_backup
{
	int		stdin_cpy;
	int		stdout_cpy;
	int		stderr_cpy;
	int		fds[50];
}				t_backup;

/*
** exec_redir.c
*/

void	get_redir(t_list *redir);

/*
** exec_cmd.c
*/

int		execute_cmd(t_ast *tree, t_sh *sh);
int		execute_cmd_bis(t_ast *tree, t_sh *sh);

int		get_status(int status);

/*
** explore_tree.c
*/

void	execute(t_ast *tree, t_sh *sh);
void	apply_redir(t_list *lst);

/*
** exec_pipe.c
*/

void	pipe_node(t_ast *tree, t_sh *sh);

#endif
