/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 17:30:28 by hdelaby           #+#    #+#             */
/*   Updated: 2017/02/18 09:00:55 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char *cmd[] = { "/bin/cat", 0 };
char *cmd1[] = { "/bin/echo", "MDR", 0};

void	runsource(int pfd[]);
void	rundest(int pfd[]);

/* int		main(void) */
/* { */
/* 	int status; */
/* 	int fd[2]; */

/* 	pipe(fd); */
/* 	runsource(fd); */
/* 	rundest(fd); */
/* 	close(fd[0]); */
/* 	close(fd[1]); */

/* 	wait(&status); */
/* 	puts("LOL"); */
/* 	exit(0); */
/* } */

void	runsource(int pfd[])
{
	int pid;

	pid = fork();
	if (!pid)
	{
		dup2(pfd[1], 1);
		close(pfd[0]);
		execvp(cmd1[0], cmd1);
	}
}

void	rundest(int pfd[])
{
	int pid;

	pid = fork();
	if (!pid)
	{
		dup2(pfd[0], 0);
		close(pfd[1]);
		execvp(cmd[0], cmd);
	}
}
