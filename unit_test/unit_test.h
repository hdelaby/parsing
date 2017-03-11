/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 11:50:59 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/11 15:40:52 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_TEST_H
# define UNIT_TEST_H

# include "libunit.h"
# include "libft.h"

int		check_stdout(char *path_to_input, char *expected_output);

int		basic_cmd(void);
int		bin_echo(void);
int		bin_echo_opt_n(void);

int		pipe_cmd(void);
int		pipe_one(void);
int		pipe_two(void);

int		semico_cmd(void);
int		semico_one(void);
int		semico_two(void);

#endif
