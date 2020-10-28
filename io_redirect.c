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

#include "exec.h"

int     redirect_grt(t_io_redirect *io)
{
	int	fd_io;
	int	filefd;

	(io->io_num == -1) ? (fd_io = STDOUT) : (fd_io = io->io_num);
	if (io->redirect_type == GRT)
		filefd = open(io->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		filefd = open(io->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (filefd < 0)
	{
		ft_putstr_fd("error at open file [fd<0]\n", STDERR);
		return (-1);
	}
	dup2(filefd, fd_io);
	if (filefd != fd_io)//should i even close(filefd) ?
		close(filefd);
	return (0);
}

int		redirect_sml(t_io_redirect *io)
{
	int	fd_io;
	int	filefd;	
	(io->io_num == -1) ? (fd_io = STDIN) : (fd_io = io->io_num);
	filefd = open(io->filename, O_RDONLY);
	if (filefd < 0)
	{
		ft_putstr_fd("error at open file [fd<0]\n", STDERR);
		return (-1);
	}
	// if (fd_io == STDIN && !ttyname(fd_io))
	// {//def_io is global and as soon as fork def_io = dup(stdin)
	// 	fd_io = dup(def_io);
	// }
	dup2(filefd, fd_io);
	if (filefd != fd_io)
		close(filefd);
	return (0);
}

int		do_heredoc(t_io_redirect *io)
{
	int		filefd;
	char	*file;
	int     fd_out;

	(io->io_num == -1) ? (fd_out = STDIN) : (fd_out = io->io_num);
	file = ft_strjoin("/tmp/.21sh_tmp_", ft_itoa((int)getpid()));
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
	unlink(file);//part of man 2[is good for 42 but not 21] ??
	free(file);
	return (0);
}

int		redirect_grt_and(t_io_redirect *io)
{
	int filefd;
	int	fd_io;
	int tmpfd;

	if (io->io_num == -1)
		fd_io = STDOUT;
	else
		fd_io = io->io_num;
	if (!is_alldigit(io->filename) && ft_strcmp("-", io->filename))
	{
		filefd = open(io->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (filefd < 0)
		{
			ft_putstr_fd("error at open file [fd<0]\n", STDERR);
			return (-1);
		}
		dup2(filefd, fd_io);
		// if (filefd != fd_io) // ?? should or shouldn t 
		// 	close(filefd);
	}
	else if (is_alldigit(io->filename))
	{
		tmpfd = ft_atoi(io->filename);
		if (!check_fd(tmpfd, STDIN))
		{
			ft_putstr_fd("shell: ", STDERR);
			ft_putnbr_fd(tmpfd, STDERR);
			ft_putstr_fd(": Bad file descriptor.\n", STDERR);
			return (-1);
		}
		dup2(tmpfd, fd_io);
	}
	else
	{
		if (close(fd_io))
		{
			ft_putstr_fd("error closing fd [bad fd]\n", STDERR);
			return (-1);
		}
	}
	return (0);
}

int		redirect_sml_and(t_io_redirect *io)
{
	int filefd;
	int	fd_io;
	int tmpfd;

	if (io->io_num == -1)
		fd_io = STDIN;
	else
		fd_io = io->io_num;
	if (!is_alldigit(io->filename) && ft_strcmp("-", io->filename))
	{
		filefd = open(io->filename, O_RDONLY);
		if (filefd < 0)
		{
			ft_putstr_fd("error at open file [fd<0]\n", STDERR);
			return (-1);
		}
		dup2(filefd, fd_io);
		// if (filefd != fd_io) // ?? should or shouldn t 
		// 	close(filefd);
	}
	else if (is_alldigit(io->filename))
	{
		tmpfd = ft_atoi(io->filename);
		if (!check_fd(tmpfd, STDIN))
		{
			ft_putstr_fd("shell: ", STDERR);
			ft_putnbr_fd(tmpfd, STDERR);
			ft_putstr_fd(": Bad file descriptor.\n", STDERR);
			return (-1);
		}
		dup2(tmpfd, fd_io);
	}
	else
	{
		if (close(fd_io))
		{
			ft_putstr_fd("error closing fd [bad fd]\n", STDERR);
			return (-1);
		}
	}
	return (0);
}

int     do_redirect(t_io_redirect *io)
{
	int     typ;

	typ = io->redirect_type;
	if (typ == GRT || typ == GRTGRT)
		return(redirect_grt(io));
	else if (typ == GRTAND)
		return(redirect_grt_and(io));
	else if (typ == SMLSML)
		return(do_heredoc(io));
	else if (typ == SML)
		return(redirect_sml(io));
	else if (typ == SMLAND)
		return (redirect_sml_and(io));
	return (0);
}