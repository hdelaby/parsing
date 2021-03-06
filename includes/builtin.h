/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:04:00 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/30 10:52:09 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "sh_error.h"
# include "libft.h"
# include "execution.h"

typedef struct	s_builtin
{
	char	*cmd;
	int		(*fct)(char **, char ***);
}				t_builtin;

int				bi_setenv(char **args, char ***env);
int				bi_unsetenv(char **args, char ***env);
int				bi_cd(char **args, char ***env);
int				cd_get_option(char *arg, int *has_opt);
int				bi_exit(char **args, char ***env);
int				bi_echo(char **args, char ***env);
int				bi_env(char **args, char ***env);

#endif
