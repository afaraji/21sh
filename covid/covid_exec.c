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

#include "../parse.h"
#include <sys/errno.h>
#include "covid_ast.c"


int		ft_exit(int status)
{
	ft_putstr("\nexit\n");
	exit(status);
}

void	ft_close(int fd)
{
	if (close(fd) == -1)
	{
		fprintf(stderr, "close: error closing fd: %d\n", fd);
	}
}

void	redirect(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) != -1)
			ft_close(oldfd); /* successfully redirected */
		else
			printf("dup2 failed..\n");
	}
}

char	*get_cmdpath(char *str, char **env)
{
	// get full path of cmd from env PATH
	char	*path;

	if (!access(str, X_OK))
	{
		return (str);
	}
	path = ft_strjoin("/bin/", str);
	if (!access(path, X_OK))
	{
		return (path);
	}
	free(path);
	path = ft_strjoin("/usr/bin/", str);
	if (!access(path, X_OK))
	{
		return (path);
	}
	free(path);
	return(str);
}


int		do_redirect(t_io_redirect *io)
{ // no error handling yet !!!
	int tmpfd;
	int filefd;
	int	fd_io;
	//io->filename(when to test if fd)

	// printf("-----[%s|%d|%d]\n", io->filename, io->io_num, io->redirect_type);
	if (io->redirect_type == GRT)
	{
		(io->io_num == -1) ? (fd_io = STDOUT) : (fd_io = io->io_num);
		tmpfd = dup(fd_io);		//??
		filefd = open(io->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (filefd < 0)
		{
			ft_putstr_fd("error at open file [fd<0]\n", 2);
			return (-1);
		}
		dup2(filefd, fd_io);
		close(filefd);
	}
	if (io->redirect_type == GRTGRT)
	{
		(io->io_num == -1) ? (fd_io = STDOUT) : (fd_io = io->io_num);
		tmpfd = dup(fd_io);
		filefd = open(io->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (filefd < 0)
		{
			ft_putstr_fd("error at open file [fd<0]\n", 2);
			return (-1);
		}
		dup2(filefd, fd_io);
		close(filefd);
	}
	if (io->redirect_type == GRTAND)// ???
	{
		(io->io_num == -1) ? (fd_io = STDOUT) : (fd_io = io->io_num);
		// if (!ft_strcmp(io->filename, "-"))
		tmpfd = dup(fd_io);		//??
		filefd = open(io->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (filefd < 0)
		{
			ft_putstr_fd("error at open file [fd<0]\n", 2);
			return (-1);
		}
		dup2(filefd, fd_io);
		close(filefd);
	}
	if (io->redirect_type == SML)
	{
		(io->io_num == -1) ? (fd_io = STDIN) : (fd_io = io->io_num);
		tmpfd = dup(fd_io);		//??
		filefd = open(io->filename, O_RDONLY);
		if (filefd < 0)
		{
			ft_putstr_fd("error at open file [fd<0]\n", 2);
			return (-1);
		}
		dup2(filefd, fd_io);
		close(filefd);
	}
	if (io->redirect_type == SMLSML)//special use case
	{
		return 1;
	}
	if (io->redirect_type == SMLAND)
	{
		(io->io_num == -1) ? (fd_io = STDIN) : (fd_io = io->io_num);
		if (!ft_strcmp(io->filename, "-"))
		{
			if (close(fd_io))
				ft_putstr_fd("error closing fd [bad fd]\n", STDERR);
			return (0);
		}
		tmpfd = dup(fd_io);		//??
		filefd = open(io->filename, O_RDONLY);
		if (filefd < 0)
		{
			ft_putstr_fd("error at open file [fd<0]\n", STDERR);
			return (-1);
		}
		dup2(filefd, fd_io);
		close(filefd);
		return 1;
	}
	return (0);
}

int		do_ass_word(t_variable *var)
{
	return 0;
}

int		do_prefix(t_cmd_prefix *prefix)
{
	t_cmd_prefix	*node;
	int				ret;

	node = prefix;
	while (node)
	{
		if (prefix->ass_word)
		{
			ret = do_ass_word(prefix->ass_word);
		}
		else if (prefix->io_redirect)
		{
			ret = do_redirect(prefix->io_redirect);
		}

		node = node->prefix;
	}
	return (ret);
}

char	**list_to_tab(t_simple_lst *list)
{
	t_simple_lst	*node;
	int		i;
	char	**args;

	node = list;
	i = 0;
	while (node)
	{
		i++;
		node = node->next;
	}
	args = (char **)malloc(sizeof(char *) * (i + 1));
	node = list;
	i = 0;
	while(node)
	{
		args[i] = ft_strdup(node->data);
		i++;
		node = node->next;
	}
	args[i] = NULL;
	//free_list(list);
	return (args);
}

int		do_suffix(t_cmd_suffix *suffix)
{
	t_cmd_suffix	*node;
	t_simple_lst			*args;
	t_simple_lst			*tmp;

	node = suffix;
	while (node)
	{
		if (node->io_redirect)
		{
			do_redirect(node->io_redirect);
		}
		node = node->suffix;
	}
	return (0);
}

int		do_simpleCmd(t_simple_cmd *cmd)
{
	int		ret;
	char	*command;

	if (cmd->prefix)
	{
		ret = do_prefix(cmd->prefix);
	}
	else if (cmd->name && cmd->suffix)
	{
		ret = do_suffix(cmd->suffix);
	}
	return (ret);
}

char	**get_args(t_simple_cmd	*cmd)
{
	t_simple_lst			*head;
	t_simple_lst			*node;
	t_cmd_suffix	*tmp;

	if (!(cmd->name) && !(cmd->word))
		return (NULL);
	head = (t_simple_lst *)malloc(sizeof(t_simple_lst));
	if (cmd->name)
		head->data = ft_strdup(cmd->name);
	else
		head->data = ft_strdup(cmd->word);
	head->next = NULL;
	node = head;
	if (cmd->suffix)
	{
		tmp = cmd->suffix;
		while (tmp)
		{
			if (tmp->word)
			{
				node->next = (t_simple_lst *)malloc(sizeof(t_simple_lst));
				node->next->data = ft_strdup(tmp->word);
				node->next->next = NULL;
				node = node->next;
			}
			tmp = tmp->suffix;
		}	
	}
	return (list_to_tab(head));
}

int		exec_ve(t_simple_cmd *s_cmd, char **env)
{
	// do redirection using ->prefix and ->suffix or do assignment

	char	**args;
	char	*cmd_path;
	t_simple_lst	*args_list;
	t_variable	*vars;
	
	if (!s_cmd)
		return (42);
	do_simpleCmd(s_cmd);
	args = get_args(s_cmd);
//	args = get_args(s_cmd->name, s_cmd->suffix);
	// fprintf(ttyfd, "======= execve: [%s:%d] =======\n", s_cmd->name,getpid());
	// for(int i = 0; args[i]; i++)
	// {
	// 	fprintf(ttyfd, "---(args:%d)---> [%s]%d\n",getpid(), args[i], i);
	// }
	if (!args)
	{
		//do word assignement perma
		return (0);
	}
	// do word assignement only for this cmd (!! assignement in child doesn't update to parent)
	// if builtin exec builtin
	cmd_path = get_cmdpath(args[0], env);
	if (execve(cmd_path, args, env) == -1)//error handling
		printf("%s:ErRoR exxecve\n",cmd_path);
	perror("PERROR");
	
	return (1);
}

int		exec_pip(t_pipe_seq *cmd, char **env)
{
	int		pfd[2];
	int		status, status2;
	pid_t	pid_l;
	pid_t	pid_r;


	if (cmd->right == NULL)
	{
		exit(exec_ve(cmd->left, env));
		printf("ERROR executing [%s]\n", cmd->left->name);
		// exit(return_value) ??
	}
	if(pipe(pfd) != 0)
		return (1);

	if ((pid_r = fork()) == -1)
		return (2);//should set errno
	if (pid_r == 0)
	{
		close(pfd[1]);
		dup2(pfd[0],STDIN);
		if (cmd->right->right)
		{
			exec_pip(cmd->right, env);
		}
		else
		{
			exit(exec_ve(cmd->right->left, env));
			printf("ERROR executing [%s]\n", cmd->right->left->name);
		}
	}
	else
	{
		if ((pid_l = fork()) == -1)
			return (2);//should set errno
		if (pid_l == 0)
		{
			//left child
			close(pfd[0]);
			dup2(pfd[1],STDOUT);
			exit(exec_ve(cmd->left, env));
			printf("ERROR executing [%s]\n", cmd->left->name);
		}
		close(pfd[0]);
		close(pfd[1]);
		int tmp;
		waitpid(pid_l, &status, 0);
		// tmp = WTERMSIG(status);
		// printf("pid_l: %d - %d\n", status, tmp);
		waitpid(pid_r, &status2, 0);
		// tmp = WTERMSIG(status2);
		// printf("pid_r: %d - %d\n", status2, tmp);
	}
	return (1);	
}

int		exec_and_or(t_and_or *cmd, char **env)
{
	int ret;

	while(cmd)
	{
	//	if cmd->dependent is OK continue if not return 1
		if(cmd->ast)
		{
			ret = exec_pip(cmd->ast, env);
		}
		cmd = cmd->next;
	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	char	*line = (char *)malloc(sizeof(char) * 1024);
	char	*str;
	int		ret = 0;
	t_cmdlist		*cmd;
	t_cmdlist		*node;

	while (1)
	{	
		gets(line);
		// printf("[%s]\n", line);
		if (ft_strncmp(line, "exit", 4) == 0)
			ft_exit(ft_atoi(&line[4]));
		
		// ret = main_parse(line);
		
		ttyfd = fopen("/dev/ttys001", "w");
		fprintf(ttyfd, "\033[H\033[2J");
		cmd = covid_main_parse(line);
		int i = 0;
		node = cmd;
		while (node)
		{
			fprintf(ttyfd, "++++++++++ (cmd: %d | BG: %d) ++++++++++\n", i, node->bg);
			i++;
			print_andor(node);
			node = node->next;
		}
		node = cmd;
		while (node)
		{
			exec_and_or(node->and_or, env);
			node = node->next;
		}
		printf("\n$> ");
	}
	
	return (0);;
}