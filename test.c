/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:13:41 by afaraji           #+#    #+#             */
/*   Updated: 2020/02/10 16:14:17 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parse.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

// char		*read_number(char *str)
// {
// 	int i;
	
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] && ft_isdigit(str[i]))
// 	{
// 		i++;
// 	}
// 	if(i == 0)
// 		return (NULL);
// 	return (ft_strsub(str, 0, i));
// }

// char		*read_word(char *str)
// {
// 	int i;

// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 	{
// 		i++;
// 	}
// 	if (i == 0)
// 		return (NULL);
// 	return (ft_strsub(str, 0, i));	
// }


/** Emulate `cmd1 | cmd2 | more` pipeline using recursion.
http://stackoverflow.com/questions/20434124/recursive-piping-in-unix-environment
*/

void	ft_close(int fd)
{
	if (close(fd) == -1)
	{
		fprintf(stderr, "close: error closing fd: %d\n", fd);
	}
}


static int child = 0; /* whether it is a child process relative to main() */

void	report_error_and_exit(const char* msg)
{
	perror(msg);
	(child ? _exit : exit)(EXIT_FAILURE);
}

/** move oldfd to newfd */
void	redirect(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) != -1)
			ft_close(oldfd); /* successfully redirected */
		else
			report_error_and_exit("dup2");
	}
}

/** execute `cmds[pos]` command and call itself for the rest of the commands.
	`cmds[]` is NULL-terminate array
	`exec_pipeline()` never returns.
*/
void	exec_pipeline(char* const* cmds[], size_t pos, int in_fd)
{
	if (cmds[pos + 1] == NULL)
	{ /* last command */
		redirect(in_fd, STDIN_FILENO); /* read from in_fd, write to STDOUT */
		execvp(cmds[pos][0], cmds[pos]);
		report_error_and_exit("execvp last");
	}
	else
	{ /* $ <in_fd cmds[pos] >fd[1] | <fd[0] cmds[pos+1] ... */
		int fd[2]; /* output pipe */
		if (pipe(fd) == -1)
			report_error_and_exit("pipe");
		switch(fork())
		{
			case -1:
				report_error_and_exit("fork");
			case 0: /* child: execute current command `cmds[pos]` */
				child = 1;
				ft_close(fd[0]); /* unused */
				redirect(in_fd, STDIN_FILENO);  /* read from in_fd */
				redirect(fd[1], STDOUT_FILENO); /* write to fd[1] */
				execvp(cmds[pos][0], cmds[pos]);
				report_error_and_exit("execvp");
			default: /* parent: execute the rest of the commands */
				ft_close(fd[1]); /* unused */
				ft_close(in_fd); /* unused */
				exec_pipeline(cmds, pos + 1, fd[0]); /* execute the rest */
		}
	}
}

int		main(int argc, char* argv[]) {
  /* `cat file | grep the | more` */
  const char* cmd1[] = { "cat" , argv[argc-1], NULL };
  const char* cmd2[] = { "grep", "int", NULL };
  const char* more[] = { "grep", "tmp", NULL };
  const char* more1[] = { "grep", ";", NULL };
  const char* more2[] = { "grep", "=", NULL };
  const char* more3[] = { "cat", "-e", NULL };
  const char* const* cmds[] = { cmd1, cmd2, more, more1, more2, more3, NULL };

  if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) /* POSIX.1-2001 reap children */
	report_error_and_exit("signal");

  exec_pipeline((char* const**)cmds, 0, STDIN_FILENO);
}