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

#include "parse.h"

void	exit_status(int status)// src: 0 form exit, 1 from return
{
	t_variable *tmp;

	g_var.exit_status = WEXITSTATUS(status);
	tmp = g_var.var;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "?"))
		{
			free(tmp->value);
			tmp->value = ft_itoa(g_var.exit_status);
			break;
		}
		tmp = tmp->next;
	}
}

int		is_alldigit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		check_fd(int fd, int io)
{
	struct stat	buffer;
	int			status;
	long		ret;

	status = fstat(fd, &buffer);
	if (io == 0)
	{
		ret = read(fd, NULL, 0);
		fprintf(ttt, "from read [%zd]\n",ret);
	}
	else
	{
		write(fd, NULL, 0);
		fprintf(ttt, "from write [%zd]\n",ret);
	}
	fprintf(ttt, "fd[%d]-->[%d:%zd]\n", fd, status, ret);
	if (status < 0 || ret < 0)
	{
		ft_putstr_fd("shell: ", STDERR);
		ft_putnbr_fd(fd, STDERR);
		ft_putstr_fd(": Bad file descriptor.\n", STDERR);
		return (0);
	}
	return (1);
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

int		do_heredoc(int fd_out, char *str)
{
	int		filefd;
	char	*file;

	file = ft_strjoin("/tmp/.21sh_tmp_", ft_itoa((int)getpid()));
	filefd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (filefd < 0)
		return (-1);
	ft_putstr_fd(str, filefd);
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

int		do_redirect(t_io_redirect *io)
{ // no error handling yet !!!
	int tmpfd;
	int filefd;
	int	fd_io;

	if (io->redirect_type == GRT)
	{
		(io->io_num == -1) ? (fd_io = STDOUT) : (fd_io = io->io_num);
		filefd = open(io->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (filefd < 0)
		{
			ft_putstr_fd("error at open file [fd<0]\n", STDERR);
			return (-1);
		}
		dup2(filefd, fd_io);
		close(filefd);
	}
	if (io->redirect_type == GRTGRT)
	{
		(io->io_num == -1) ? (fd_io = STDOUT) : (fd_io = io->io_num);
		filefd = open(io->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (filefd < 0)
		{
			ft_putstr_fd("error at open file [fd<0]\n", STDERR);
			return (-1);
		}
		dup2(filefd, fd_io);
		close(filefd);
	}
	if (io->redirect_type == GRTAND)
	{
		(io->io_num == -1) ? (fd_io = STDOUT) : (fd_io = io->io_num);		
		if (!is_alldigit(io->filename) && ft_strcmp("-", io->filename))
		{
			filefd = open(io->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (filefd < 0)
			{
				ft_putstr_fd("error at open file [fd<0]\n", STDERR);
				return (-1);
			}
			dup2(filefd, fd_io);
		}
		else if (is_alldigit(io->filename))
		{
			tmpfd = ft_atoi(io->filename);
			if (!check_fd(tmpfd, STDOUT))
				return (-1);
			dup2(tmpfd, fd_io);
		}
		else
		{
			close(fd_io);
		}
	}
	if (io->redirect_type == SML)
	{
		(io->io_num == -1) ? (fd_io = STDIN) : (fd_io = io->io_num);
		filefd = open(io->filename, O_RDONLY);
		if (filefd < 0)
		{
			ft_putstr_fd("error at open file [fd<0]\n", STDERR);
			return (-1);
		}
		dup2(filefd, fd_io);
		close(filefd);
	}
	if (io->redirect_type == SMLSML)
	{
		(io->io_num == -1) ? (fd_io = STDIN) : (fd_io = io->io_num);
		return (do_heredoc(fd_io, io->filename));
	}
	if (io->redirect_type == SMLAND)
	{
		(io->io_num == -1) ? (fd_io = STDIN) : (fd_io = io->io_num);
		if (!is_alldigit(io->filename) && ft_strcmp("-", io->filename))
		{
			filefd = open(io->filename, O_RDONLY);
			if (filefd < 0)
			{
				ft_putstr_fd("error at open file [fd<0]\n", STDERR);
				return (-1);
			}
			dup2(filefd, fd_io);
			close(filefd);
		}
		else if (is_alldigit(io->filename))
		{
			tmpfd = ft_atoi(io->filename);
			if (!check_fd(tmpfd, STDIN))
				return (-1);
			dup2(tmpfd, fd_io);
		}
		else
		{
			if (close(fd_io))
				ft_putstr_fd("error closing fd [bad fd]\n", STDERR);
		}
	}
	return (0);
}

t_variable	*var_dup(t_variable *var)
{
	t_variable	*node;

	node = (t_variable *)malloc(sizeof(t_variable));
	node->env = var->env;
	node->key = ft_strdup(var->key);
	node->value = ft_strdup(var->value);
	node->next = NULL;
	return (node);
}

int		do_assignement(t_cmd_prefix *pref, t_variable *head, int env)
{
	t_cmd_prefix	*node;
	t_variable		*tmp;
	int				state;

	node = pref;
	while (node)
	{
		if (node->ass_word)
		{
			tmp = head;
			state = 0;
			node->ass_word->env = (node->ass_word->env == 2) ? 2: env;// ???
			while (tmp)
			{
				if (tmp->env != 2 && !ft_strcmp(tmp->key, node->ass_word->key))
				{
					tmp->env = node->ass_word->env;
					free(tmp->value);
					tmp->value = ft_strdup(node->ass_word->value);
					state = 1;
					break;
				}
				tmp = tmp->next;
			}
			if (!state)
			{
				tmp = head;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = var_dup(node->ass_word);
			}
		}
		node = node->prefix;
	}
	return (0);
}

int		do_prefix(t_cmd_prefix *prefix, t_variable *var, int env)
{
	t_cmd_prefix	*node;
	int				ret = 0;

	do_assignement(prefix, var, env);
	node = prefix;
	while (node)
	{
		if (node->io_redirect)
		{
			ret = do_redirect(node->io_redirect);
		}

		node = node->prefix;
	}
	return (ret);
}

char	**paths_from_env(void)
{
	char	**paths;
	char	*tmp;
	int i;

	tmp = fetch_variables("PATH", -1);
	paths = ft_strsplit(tmp, ':');
	free(tmp);
	i = 0;
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = tmp;
		i++;
	}
	paths[i] = NULL;
	return (paths);
}

char	*get_cmdpath(char *str)
{
	char	**paths;
	int		i;
	char	*tmp;

	if (!access(str, F_OK))
	{
		return (ft_strdup(str));
	}
	if (!(paths = paths_from_env()))
		return(NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], str);
		if (!access(tmp, F_OK))
		{
			return (tmp);
		}
		free(tmp);
		i++;
	}
	return(NULL);
}

int		env_tab_count(int all)
{
	t_variable	*node;
	int			count;
	
	node = g_var.var;
	count = 0;
	while (node)
	{
		if (node->env == 0 || all)
			count++;
		node = node->next;
	}
	return (count);
}

char	**env_to_tab(t_variable *var, int all)
{
	t_variable	*node;
	char		**argv;
	char		*tmp;
	int			i;
	
	node = var;
	i = env_tab_count(all);	
	if (!(argv = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (node)
	{
		if (node->env == 0 || all)
		{
			tmp = ft_strjoin(node->key, "=");
			argv[i] = ft_strjoin(tmp, node->value);
			free(tmp);
			i++;
		}
		node = node->next;
	}
	argv[i] = NULL;
	if (i == 0)
		return (NULL);
	return (argv);
}

int		do_suffix(t_cmd_suffix *suffix)
{
	t_cmd_suffix	*node;
	t_l	*args;
	t_l	*tmp;
	int				ret = 0;

	node = suffix;
	while (node)
	{
		if (node->io_redirect)
		{
			ret = do_redirect(node->io_redirect);
		}
		node = node->suffix;
	}
	return (ret);
}

int		do_simpleCmd(t_simple_cmd *cmd)
{
	int		ret = 0;
	char	*command;

	if (cmd->prefix)
	{
		ret = do_prefix(cmd->prefix, g_var.var, 0);
	}
	if (ret != 0)
		return (ret);
	if ((cmd->name || cmd->word) && cmd->suffix)
	{
		ret = do_suffix(cmd->suffix);
	}
	return (ret);
}

char	**list_to_tab(t_l *list)
{
	t_l	*node;
	int		i;
	char	**args;

	if (!list)
		return (NULL);
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

t_l	*get_args(t_simple_cmd	*cmd)
{
	t_l			*head;
	t_l			*node;
	t_cmd_suffix	*tmp;

	if (!(cmd->name) && !(cmd->word))
		return (NULL);
	head = (t_l *)malloc(sizeof(t_l));
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
				node->next = (t_l *)malloc(sizeof(t_l));
				node->next->data = ft_strdup(tmp->word);
				node->next->next = NULL;
				node = node->next;
			}
			tmp = tmp->suffix;
		}	
	}
	return (head);
}

int		is_builtin(char *str)
{
	char	*b_in_list[] = {"echo", "export", "cd", "setenv", "unsetenv", "env", NULL};
	int		i;

	i = 0;
	while (b_in_list[i])
	{
		if (!ft_strcmp(b_in_list[i], str))
			return (i + 1);
		i++;
	}
	return (0);
}

t_l	*var_sub(t_l *head)
{
	t_l	*node;
	t_l	*next_node;
	char			*tmp;
	char			**t;
	int				i;

	next_node = head->next;
	tmp = str_dollar_sub(head->data); // node->data is freed.
	t = ft_strsplit(tmp, ' ');
	free(tmp);
	i = 1;
	if (!t || !t[0])
	{
		head->data = ft_strdup("");
		return (head);
	}
	head->data = ft_strdup(t[0]);
	node = head;
	while (t[i])
	{
		node->next = (t_l *)malloc(sizeof(t_l));
		node->next->data = ft_strdup(t[i]);
		node->next->next = NULL;
		node = node->next;
		i++;
	}
	node->next = next_node;
	return (head);
}

char	**get_arg_var_sub(t_simple_cmd *cmd)
{
	t_l	*list;
	t_l	*node;

	list = get_args(cmd);
	node = list;
	while (node)
	{
		if (is_dollar(node->data) > -1)
		{
			node = var_sub(node);
		}
		node = node->next;
	}
	return (list_to_tab(list));
}

int		exec_simple_cmd(t_simple_cmd *cmd)
{
	char	**args;
	char	**env;
	char	*cmd_path;
	t_l	*args_list;
	t_variable	*vars;
fprintf(ttt,"---------[simpleCmd]------------\n");
	if (!cmd)
		return (404);
	if (do_simpleCmd(cmd))//does prefix and suffix
		return (1);
	args = get_arg_var_sub(cmd);
	if (!args)
		exit (0);
	env = env_to_tab(g_var.var, 0);
	// if builtin exec builtin
	if (is_builtin(args[0]))
	{
		//do builtin
		return (builtins(args[0], args, env));
	}
	if (!(cmd_path = get_cmdpath(args[0])))
	{
		printf("shell: command not found: %s\n",args[0]);
		return (127);
	}
	// ft_set_attr(1);
	fprintf(ttt,"---------[simpleCmd -> execve]------------\n");
	execve(cmd_path, args, env);//error handling
	printf("shell: permission denied: %s\n", args[0]);
	return (126);
}

int		exec_pipe(t_pipe_seq *cmd)
{
	int		pfd[2];
	int		status;
	pid_t	pid_l;
	pid_t	pid_r;


	if (cmd->right == NULL)
	{
		exit(exec_simple_cmd(cmd->left));
		// exit(return_value) ?? should exit or not ?
	}
	if(pipe(pfd) != 0)
		return (1);

	if ((pid_l = fork()) == -1)
		return (2);//should set errno
	if (pid_l == 0)
	{
		//left child
		close(pfd[0]);
		dup2(pfd[1],STDOUT);
		exit(exec_simple_cmd(cmd->left));
	}
	else
	{
		if ((pid_r = fork()) == -1)
			return (2);//should set errno
		if (pid_r == 0)
		{
			close(pfd[1]);
			dup2(pfd[0],STDIN);
			if (cmd->right->right)
			{
				exec_pipe(cmd->right);
			}
			else
			{
				exit(exec_simple_cmd(cmd->right->left));
			}
		}
		close(pfd[0]);
		close(pfd[1]);
		int tmp;// to be deleted after testing
		waitpid(pid_l, &tmp, 0);
		waitpid(pid_r, &status, 0);
		fprintf(ttt,"child_l:[%d] exit(%d)\n", pid_l, tmp);
		fprintf(ttt,"child_r:[%d] exit(%d)\n", pid_r, status);
		exit(WEXITSTATUS(status));
	}
	return (0);
}

t_variable	*var_list_dup(t_variable *src)
{
	t_variable	*node;
	t_variable	*tmp;
	t_variable	*head;

	head = var_dup(src);
	node = src;
	tmp = head;
	while (node->next)
	{
		tmp->next = var_dup(node->next);
		tmp = tmp->next;
		node = node->next;
	}
	return (head);
}

void	reset_in_out(int in, int out, int err)
{
	dup2(in, STDIN);
	close(in);
	dup2(out, STDOUT);
	close(out);
	dup2(err, STDERR);
	close(err);
}

int		exec_ast(t_pipe_seq *cmd, int bg)
{
	char		**av;
	char		**env;
	int			child;
	t_variable	*tmp;
	int			status;
	int			in;
	int			out;
	int			err;

	if (cmd->right == NULL && !bg)
	{
		av = get_arg_var_sub(cmd->left);
		if (av && is_builtin(av[0]))
		{
			in = dup(STDIN);
			out = dup(STDOUT);
			err = dup(STDERR);
			tmp = var_list_dup(g_var.var);
			if (do_prefix(cmd->left->prefix, tmp, 0) || do_suffix(cmd->left->suffix))
				return (1);
			// fprintf(ttt, "--------------------------\n");
			// for (t_variable *ll=tmp; ll; ll=ll->next)
			// 	fprintf(ttt, "[%d|%s:%s]\n", ll->env,ll->key,ll->value);
			env = env_to_tab(tmp, 0);
			// fprintf(ttt, "-+--+-+-+-+-+-+-+-+-+-+-+-\n");
			// for (int i = 0; env[i];i++)
			// 	fprintf(ttt, "%s\n", env[i]);
			//free(tmp);
			//free(av);
			status = builtins(av[0], av, env);
			reset_in_out(in, out, err);
			// free(env);
			// free(av);
			return (status);
		}
		if (!(cmd->left->name) && !(cmd->left->word))
		{
			in = dup(STDIN);
			out = dup(STDOUT);
			err = dup(STDERR);
			status = do_prefix(cmd->left->prefix, g_var.var, 1);
			reset_in_out(in, out, err);
			return (status);
		}
	}
	fprintf(ttt, "==+++++++++++++++++++++++++=>bg:[%d]\n", bg);
	status = 0;
	child = fork();
	if (child == 0)
	{
		exec_pipe(cmd);
	}
	else if (!bg)
	{
		waitpid(child, &status, 0);
		exit_status(status);
		fprintf(ttt,"P_child:[%d] exit(%d) - (%d)\n", child, WEXITSTATUS(status) , g_var.exit_status);
	}
	else
	{
		fprintf(ttt, "==++++++not waiting++++++\n");
		add_proc(child);
	}
	
	return (status);
}

int		execute(t_and_or *cmd, int bg)
{
	int dp;
	int ret = 0;

	// exec cmdA1 | cmdA2 && cmdB1 | cmdB2 || cmdC
		// sleep(5);
	while (cmd)
	{
		dp = cmd->dependent;
		if (!dp || (dp == 1 && !g_var.exit_status) || (dp == 2 && g_var.exit_status))
		{
			exit_status(exec_ast(cmd->ast, bg));
			fprintf(ttt, "===exit stats[%d]===\n", g_var.exit_status);
		}
		cmd = cmd->next;
	}	
	return (ret);
}//lol=1xxxxxx  env | grep lol

// int		execute(t_and_or *cmd, int bg)
// {
// 	ttt = fopen("/dev/ttys004", "w");
// 	int dp;
// 	int ret = 0;
// 	int child_pid;

// 	// need to fork here
// 	if ((child_pid = fork()) == -1)
// 		return (10);	// should set g_var.errno
// 	if (child_pid == 0)
// 	{// exec cmd | cmd && cmd | cmd || cmd
// 		// sleep(5);
// 		while (cmd)
// 		{
// 			dp = cmd->dependent;
// 			if (!dp || (dp == 1 && !g_var.exit_status) || (dp == 2 && g_var.exit_status))
// 			{
// 				ret = exec_ast(cmd->ast);// here should go exec_pipe();
// 				g_var.exit_status = ret;
// 			}
// 			cmd = cmd->next;
// 		}
// 		exit(0);
// 	}
// 	if (child_pid && !bg)
// 	{
// 		int status;
// 		waitpid(child_pid, &status, 0); // should it be &ret instead of NULL to get exitstatus of child ?
// 		g_var.exit_status = status;
// 	}
// 	return (ret);
// }
