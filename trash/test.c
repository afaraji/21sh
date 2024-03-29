/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 23:14:10 by afaraji           #+#    #+#             */
/*   Updated: 2020/02/11 23:14:15 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

// int sig;

// void	signal_callback_handler(int signum)
// {
// 	if (signum == 2)
// 	{
// 		printf("ctrl-c\n");
// 		sig = 1;
// 	}
// }


// int main()
// {
// 	int buff;
// 	sig = 0;
// 	signal(SIGINT, &signal_callback_handler);
// 	struct termios term;

// 	tcgetattr(0, &term);
// 	term.c_lflag &= ~(ICANON | ECHO | ISIG );
// 	tcsetattr(0, TCSANOW, &term);
// 	while (1)
// 	{
// 		buff = 0;
// 		if (sig)
// 			break;
// 		int ret = read(0, &buff, 4);
// 		if (sig)
// 			break;
// 		printf("==+[%d]+[%X]==\n", ret, buff);
// 		if (buff == 0x9)
// 			sig = 1;
// 		if (sig)
// 			break;
// 	}
// 	sig = 0;
// 	return (0);
// }

// typedef struct			s_mem_alloc
// {
// 	void				*ptr;
// 	struct s_mem_alloc	*next;

// }						t_mem_alloc;

// void	*myMalloc(size_t size)
// {
// 	static t_mem_alloc	*head = NULL;
// 	void				*data;
// 	t_mem_alloc			*node;

// 	if (head == NULL)
// 	{
// 		head = (t_mem_alloc *)malloc(sizeof(t_mem_alloc));
// 		head->next = NULL;
// 		head->ptr = head;
// 		return (NULL);
// 	}
// 	node = head;
// 	while (node->next)
// 	{
// 		node = node->next;
// 	}
// 	data = malloc(size);
// 	node->next = NULL;
// 	node->ptr = data;
// 	return (data);
// }

// int main(int ac, char **av)
// {
// 	FILE	*fd;

// 	fd = fopen("/tmp/closed_fd", "w");
// 	fprintf(fd,"===> main [%s][%s][%s]\n", ttyname(0), ttyname(1), ttyname(2));
// 	return (0);
// }

int main(int ac, char **av)
{
	int fd;

	fd = open("fofo", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	return (0);
}


int		tilde_sub(t_list_token **cmd_token)// need to be normed and leak free
{// neeed to add ass_word
	char 			*tmp = NULL;
	char			*str;
	char 			*tilde_prefix;
	char 			*rest;
	t_list_token	*node;
	struct passwd	*pw;
	int				i;

	node = *cmd_token;
	while (node)
	{
		if (node->type != WORD || (node->next && (node->next->type == QUOTE || node->next->type == DQUOTE)))
		{
			node = node->next;
			continue;
		}
		if ((i = is_assword(node->data)))
			str = ft_strdup(&(node->data[i]));
		else
			str = ft_strdup(node->data);
		if (str && str[0] == '~')
		{
			i = 1;
			while (str[i] && str[i] != '/')
				i++;
			(str[i] == '/') ? (rest = ft_strdup(&(str[i]))) : (rest = ft_strdup(""));
			tilde_prefix = ft_strsub(str, 1, i - 1);
			if (!ft_strcmp(tilde_prefix, ""))
			{// $HOME
				tmp = fetch_variables("HOME", -1);
				if (tmp)
				{
					ft_strdel(&str);
					str = ft_strjoin(tmp, rest);
				}
				else
				{
					pw = getpwuid(getuid());
					ft_strdel(&str);
					if (pw)
						str = ft_strjoin(pw->pw_dir, rest);
				}
			}
			else if(!ft_strcmp(tilde_prefix, "-"))
			{// $OLDPWD | ~-
				tmp = fetch_variables("OLDPWD", -1);
				if(tmp)
				{
					ft_strdel(&str);
					str = ft_strjoin(tmp, rest);
				}
			}
			else if (!ft_strcmp(tilde_prefix, "+"))
			{// $PWD
				tmp = fetch_variables("PWD", -1);
				if(tmp)
				{
					ft_strdel(&str);
					str = ft_strjoin(tmp, rest);
				}
			}
			else
			{
				tmp = ft_strjoin("/Users/", tilde_prefix);
				if (!access(tmp, F_OK))
				{
					ft_strdel(&str);
					str = ft_strjoin(tmp, rest);
				}
			}
			ft_strdel(&rest);
			ft_strdel(&tilde_prefix);
			if (tmp)
				ft_strdel(&tmp);
			if ((i = is_assword(node->data)))
			{
				node->data[i] = '\0';
				tmp = ft_strjoin(node->data, str);
				ft_strdel(&(node->data));
				ft_strdel(&str);
				node->data = tmp;
			}
			else
			{
				ft_strdel(&(node->data));
				node->data = str;
			}
		}
		node = node->next;
	}
	return (0);
}

// int		here_doc(t_io_redirect	*io)
// {
// 	// if (io->io_num >= 0) ?
// 	char	*str;
// 	char	*tmp;
// 	char	*buff;

// 	ft_prompt("here--doc> ");
// 	tmp = ft_strdup("");
// 	while (get_next_line(0, &buff))
// 	{
// 		if (!ft_strcmp(buff, io->filename) || !ft_strcmp(buff, "\x04"))
// 		{
// 			if (!str)
// 				str = ft_strdup("");
// 			ft_putstr_fd(str, STDIN);
// 			free(str);
// 			free(tmp);
// 		}
// 		str = ft_strjoin(tmp, buff);
// 		free(tmp);
// 		tmp = str;
// 	}
// 	return (0);
// }

// int		do_redirect(t_io_redirect *io)
// { // no error handling yet !!!
// 	int tmpfd;
// 	int filefd;
// 	int	fd_io;

// 	if (io->redirect_type == GRT)
	// {
	// 	(io->io_num == -1) ? (fd_io = STDOUT) : (fd_io = io->io_num);
	// 	filefd = open(io->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	// 	if (filefd < 0)
	// 	{
	// 		ft_putstr_fd("error at open file [fd<0]\n", STDERR);
	// 		return (-1);
	// 	}
	// 	dup2(filefd, fd_io);
	// 	if (filefd != fd_io)
	// 		close(filefd);
	// }
	// if (io->redirect_type == GRTGRT)
	// {
	// 	(io->io_num == -1) ? (fd_io = STDOUT) : (fd_io = io->io_num);
	// 	filefd = open(io->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	// 	if (filefd < 0)
	// 	{
	// 		ft_putstr_fd("error at open file [fd<0]\n", STDERR);
	// 		return (-1);
	// 	}
	// 	dup2(filefd, fd_io);
	// 	if (filefd != fd_io)
	// 		close(filefd);
	// }
	// if (io->redirect_type == SMLSML)
	// {
	// 	(io->io_num == -1) ? (fd_io = STDIN) : (fd_io = io->io_num);
	// 	return (do_heredoc(io));
	// }
	// if (io->redirect_type == SML)
	// {
	// 	(io->io_num == -1) ? (fd_io = STDIN) : (fd_io = io->io_num);
	// 	filefd = open(io->filename, O_RDONLY);
	// 	if (filefd < 0)
	// 	{
	// 		ft_putstr_fd("error at open file [fd<0]\n", STDERR);
	// 		return (-1);
	// 	}
	// 	int tmp = check_fd(fd_io, 0);
	// 	// fprintf(ttyfd, "====12321321===[%d]==fd_io=[%d][%s]\n", tmp, fd_io, ttyname(fd_io));
	// 	if (fd_io == STDIN && !ttyname(fd_io))
	// 	{
	// 		fd_io = dup(def_io);
	// 		// fprintf(ttyfd, "-------*--->[%d][%s]\n", fd_io, ttyname(fd_io));
	// 	}
	// 	dup2(filefd, fd_io);
	// 		// if (filefd != fd_io)
	// 	// close(filefd);
	// }
// 	if (io->redirect_type == GRTAND)
// 	{
// 		// fprintf(ttyfd, "----- here >&- ------\n");
// 		(io->io_num == -1) ? (fd_io = STDOUT) : (fd_io = io->io_num);
// 		if (!is_alldigit(io->filename) && ft_strcmp("-", io->filename))
// 		{
// 			filefd = open(io->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 			if (filefd < 0)
// 			{
// 				ft_putstr_fd("error at open file [fd<0]\n", STDERR);
// 				return (-1);
// 			}
// 			dup2(filefd, fd_io);
// 		}
// 		else if (is_alldigit(io->filename))
// 		{
// 			tmpfd = ft_atoi(io->filename);
// 			if (!check_fd(tmpfd, STDOUT))
// 				return (-1);
// 			dup2(tmpfd, fd_io);
// 		}
// 		else
// 		{
// 			int ret = close(fd_io);
// 			// fprintf(ttyfd,"----> closing[%d]----> close[%d]---\n", fd_io, ret);
// 			// fprintf(ttyfd,"----> ttyname [%s]---\n", ttyname(fd_io));
// 		}
// 	}
// 	if (io->redirect_type == SMLAND)
// 	{
// 		(io->io_num == -1) ? (fd_io = STDIN) : (fd_io = io->io_num);
// 		if (!is_alldigit(io->filename) && ft_strcmp("-", io->filename))
// 		{
// 			filefd = open(io->filename, O_RDONLY);
// 			if (filefd < 0)
// 			{
// 				ft_putstr_fd("error at open file [fd<0]\n", STDERR);
// 				return (-1);
// 			}
// 			dup2(filefd, fd_io);
// 			if (filefd != fd_io)
// 				close(filefd);
// 		}
// 		else if (is_alldigit(io->filename))
// 		{
// 			tmpfd = ft_atoi(io->filename);
// 			if (!check_fd(tmpfd, STDIN))
// 				return (-1);
// 			dup2(tmpfd, fd_io);
// 		}
// 		else
// 		{
// 			if (close(fd_io))
// 			{
// 				ft_putstr_fd("error closing fd [bad fd]\n", STDERR);
// 				return (-1);
// 			}
// 		}
// 	}
// 	return (0);
// }
