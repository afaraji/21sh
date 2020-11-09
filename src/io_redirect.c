/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:33:28 by afaraji           #+#    #+#             */
/*   Updated: 2020/10/28 13:33:36 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int	redirect_grt(t_io_redirect *io)
{
	int	fd_io;
	int	filefd;

	io->filename = str_dollar_sub(io->filename);
	if (io->io_num == -1)
		fd_io = STDOUT;
	else
		fd_io = io->io_num;
	if (io->redirect_type == GRT)
		filefd = open(io->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		filefd = open(io->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (filefd < 0)
	{
		ft_print(STDERR, "shell: %s: Permission denied.\n", io->filename);
		return (-1);
	}
	dup2(filefd, fd_io);
	if (filefd != fd_io)
		close(filefd);
	return (0);
}

int	redirect_sml(t_io_redirect *io)
{
	int	fd_io;
	int	filefd;

	io->filename = str_dollar_sub(io->filename);
	if (io->io_num == -1)
		fd_io = STDIN;
	else
		fd_io = io->io_num;
	filefd = open(io->filename, O_RDONLY);
	if (filefd < 0)
	{
		if (!access(io->filename, F_OK))
			ft_print(STDERR, "shell: %s: Permission denied.\n", io->filename);
		else
			ft_print(STDERR, "shell: %s: No such file or directory.\n",
																io->filename);
		return (-1);
	}
	dup2(filefd, fd_io);
	if (filefd != fd_io)
		close(filefd);
	return (0);
}

int	do_heredoc(t_io_redirect *io)
{
	int		filefd;
	char	*file;
	int		fd_out;
	char	*tmp;

	if (io->io_num == -1)
		fd_out = STDIN;
	else
		fd_out = io->io_num;
	tmp = ft_itoa((int)getpid());
	file = ft_strjoin("/tmp/.21sh_tmp_", tmp);
	ft_strdel(&tmp);
	filefd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (filefd < 0)
		return (-1);
	ft_putstr_fd(io->filename, filefd);
	close(filefd);
	filefd = open(file, O_RDONLY);
	if (filefd < 0)
		return (-1);
	dup2(filefd, fd_out);
	close(filefd);
	unlink(file);
	free(file);
	return (0);
}

int	do_redirect(t_io_redirect *io)
{
	int	typ;

	typ = io->redirect_type;
	if (typ == GRT || typ == GRTGRT)
		return (redirect_grt(io));
	else if (typ == GRTAND)
		return (redirect_grt_and(io));
	else if (typ == SMLSML)
		return (do_heredoc(io));
	else if (typ == SML)
		return (redirect_sml(io));
	else if (typ == SMLAND)
		return (redirect_sml_and(io));
	return (0);
}
