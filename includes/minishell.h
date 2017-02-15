/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 16:29:49 by hdelaby           #+#    #+#             */
/*   Updated: 2017/01/28 10:58:07 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "sh_error.h"
# include "signal_handling.h"

# define DEFAULT_PATH "/sbin:/bin:/usr/sbin:/usr/bin"

typedef struct	s_builtin
{
	char	*cmd;
	int		(*fct)(char **, t_list **);
}				t_builtin;

/*
** PARSING
*/

char			**cmd_parsing(char **str);
char			**input_token(char *str);

/*
** CORE SH
*/

int				apply_bin(char *cmd, char **args, t_list **env);
int				exec_home(char *cmd, char **args, t_list **env);

/*
** TOOLS
*/

int				cmp_find_env(char *content, char *env_var);
char			*ft_canon_path(char **path);

/*
** GETTERS
*/

int				get_exit_status(int status);
t_list			**get_global_env(t_list **env);

/*
** ENV
*/

char			*ft_getenv(const char *name, t_list **env);
int				ft_setenv(const char *name, const char *value, int overwrite,
		t_list **env);
int				ft_unsetenv(const char *name, t_list **env);

/*
** DISPLAY
*/

void			put_prompt(t_list **env);

/*
** BUILTINS
*/

int				bi_echo(char **args, t_list **env);
int				bi_cd(char **args, t_list **env);
int				cd_get_option(char *arg, int *has_opt);
int				bi_env(char **args, t_list **env);
int				bi_exit(char **args, t_list **env);
int				bi_setenv(char **args, t_list **env);
int				bi_unsetenv(char **args, t_list **env);

#endif
