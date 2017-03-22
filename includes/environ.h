/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 11:55:09 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/22 14:33:24 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# include "libft.h"

char	*ft_getenv(const char *name, char **env);
int		ft_setenv(const char *name, const char *value, int overwrite, char ***env);
int		ft_unsetenv(const char *name, char ***env);
char	**ft_tabremove(char **ta, size_t index);

#endif
