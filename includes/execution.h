/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:49:47 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/21 12:10:52 by hdelaby          ###   ########.fr       */
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

void	execute(t_ast *tree, t_sh *sh);

#endif
