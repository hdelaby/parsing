/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 11:40:42 by hdelaby           #+#    #+#             */
/*   Updated: 2017/02/18 11:46:59 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

# define MAX_TOKEN_LEN 256

typedef struct	s_token
{
	char	str[MAX_TOKEN_LEN];
	int		cmd_i;
	int		str_i;
}				t_token;

/*
** SPECIAL OPERATORS
** ';' '|' '>' '<' '<<' '>>' '&'
*/

#endif
