/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libunit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 11:00:12 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/07 16:46:06 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUNIT_H
# define LIBUNIT_H

# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_unit_test
{
	int					(*func)(void);
	const char			*name;
	struct s_unit_test	*next;
	int					status;
}				t_unit_test;

int				run_unit_test(int (*func)(void));
int				load_test(t_unit_test **list, const char *name,
		int (*func)(void));
int				launch_tests(t_unit_test *list);

#endif
