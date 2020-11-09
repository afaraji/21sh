/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect_aggr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 19:06:11 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 19:06:18 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int		redirect_dup_close(char *io_file, int fd_io, int in_out)
{
	int tmpfd;

	if (is_alldigit(io_file))
	{
		tmpfd = ft_atoi(io_file);
		tmpfd = (tmpfd < 0) ? -1 : tmpfd;
		if (!check_fd(tmpfd, in_out))
		{
			ft_print(STDERR, "shell: %d: Bad file descriptor.\n", tmpfd);
			return (-1);
		}
		dup2(tmpfd, fd_io);
	}
	else
	{
		if (close(fd_io))
		{
			ft_print(STDERR, "shell: %d: Bad file descriptor.\n", fd_io);
			return (-1);
		}
	}
	return (0);
}

int		redirect_sml_and(t_io_redirect *io)
{
	int filefd;
	int	fd_io;

	fd_io = (io->io_num == -1) ? STDIN : io->io_num;
	io->filename = str_dollar_sub(io->filename);
	if (!is_alldigit(io->filename) && ft_strcmp("-", io->filename))
	{
		filefd = open(io->filename, O_RDONLY);
		if (filefd < 0)
		{
			if (!access(io->filename, F_OK))
				ft_print(STDERR, "shell: %s: Permission denied.\n",
																io->filename);
			else
				ft_print(STDERR, "shell: %s: No such file or directory.\n",
																io->filename);
			return (-1);
		}
		dup2(filefd, fd_io);
	}
	else
		return (redirect_dup_close(io->filename, fd_io, STDIN));
	return (0);
}

int		redirect_grt_and(t_io_redirect *io)
{
	int filefd;
	int	fd_io;

	fd_io = (io->io_num == -1) ? STDOUT : io->io_num;
	io->filename = str_dollar_sub(io->filename);
	if (!is_alldigit(io->filename) && ft_strcmp("-", io->filename))
	{
		filefd = open(io->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (filefd < 0)
		{
			ft_print(STDERR, "shell: %s: Permission denied.\n", io->filename);
			return (-1);
		}
		dup2(filefd, fd_io);
	}
	else
		return (redirect_dup_close(io->filename, fd_io, STDOUT));
	return (0);
}
