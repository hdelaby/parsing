/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 13:10:07 by hdelaby           #+#    #+#             */
/*   Updated: 2017/01/27 10:35:55 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ERROR_H
# define SH_ERROR_H

# include "minishell.h"

# define E_NOENT "No such file or directory"
# define E_ACCES "Permission denied"
# define E_NOCMD "Command not found"
# define E_EINVAL "Invalid argument"

int		ft_puterr(char *program, char *errmsg, char *arg, int error_code);

#endif
