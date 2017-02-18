/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:20:46 by hdelaby           #+#    #+#             */
/*   Updated: 2017/02/15 17:30:19 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "fcntl.h"

char		**parsing(char *line)
{
	char	**tab;
	
	tab = ft_strsplit(line, ';');
	return (tab);
}

int			test_pipe(char **argv)
{
	int	fildes[2];
	pid_t	pid;
	char	buf;

	if (pipe(fildes) == -1)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		close(fildes[1]);
		while (read(fildes[0], &buf, 1) > 0)
			write(STDOUT_FILENO, &buf, 1);
		write(STDOUT_FILENO, "\n", 1);
		close(fildes[0]);
		return (0);
	}
	else
	{
		close(fildes[0]);
		write(fildes[1], argv[1], ft_strlen(argv[1]));
		close(fildes[1]);
		wait(NULL);
		return (0);
	}
	return (0);
}

void	test_redir_output(void)
{
	int fd;
	int fd2;

	fd = open("lol", O_WRONLY);
	fd2 = open("toto", O_WRONLY);
	dup2(fd, STDERR_FILENO);
	dup2(fd2, STDERR_FILENO);
	ft_putstr_fd("ptdr des barres", 2);
}

int		test_redir_input(char **av, char **env)
{
	int	fd;

	fd = open("lol", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	execve(av[1], av + 1, env);
	return (0);
}
