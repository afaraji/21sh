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
#include "exec.h"

int		def_io;

void	exit_status(int status)
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
		// fprintf(ttt, "from read [%zd]\n",ret);
	}
	else
	{
		ret = write(fd, NULL, 0);
		// fprintf(ttt, "from write [%zd]\n",ret);
	}
	// fprintf(ttt, "fd[%d]-->[%d:%zd]\n", fd, status, ret);
	if (status < 0 || ret < 0)
		return (0);
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

t_variable	*var_dup(t_variable *var)
{
	t_variable	*node;

	node = (t_variable *)malloc(sizeof(t_variable));
	if (!node)
		return (NULL);
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
					ft_strdel(&(tmp->value));
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
			if (ret != 0)
				return (ret);
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
	if (!tmp)
		return (NULL);
	paths = ft_strsplit(tmp, ':');
	ft_strdel(&tmp);
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
		return (ft_strdup(str));
	if (is_path(str))
	{
		ft_print(STDERR, "shell: %s: No such file or directory\n",str);
		return (NULL);
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
		ft_strdel(&tmp);
		i++;
	}
	ft_print(STDERR, "shell: command not found: %s\n", str);
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
			ft_strdel(&tmp);
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
			if (ret != 0)
				return (ret);
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
		if (ft_strcmp(node->data, ""))
			i++;
		node = node->next;
	}
	if (!(args = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	node = list;
	i = 0;
	while(node)
	{
		if (ft_strcmp(node->data, ""))
		{
			args[i] = ft_strdup(node->data);
			i++;
		}
		node = node->next;
	}
	args[i] = NULL;
	//free_list(list);
	return (args);
}

t_l		*get_args(t_simple_cmd	*cmd)
{
	t_l				*head;
	t_l				*node;
	t_cmd_suffix	*tmp;

	if (!(cmd->name) && !(cmd->word))
		return (NULL);
	if (!(head = (t_l *)malloc(sizeof(t_l))))
		return (NULL);
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
	char	*b_in_list[] = {"echo", "export", "cd", "setenv", "unsetenv", "env", "exit", NULL};
	int		i;

	if (!str || !ft_strcmp(str, ""))
		return (0);
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
	ft_strdel(&tmp);
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
	char		**args;
	char		**env;
	char		*cmd_path;
	t_l			*args_list;
	t_variable	*vars;

	if (!cmd)
		return (404);
	if (do_simpleCmd(cmd))//does prefix and suffix
		return (1);
	args = get_arg_var_sub(cmd);
	if (!args || !args[0])
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
		return (127);
	}
	ft_set_attr(1);
	execve(cmd_path, args, env);//error handling
	ft_print(STDERR, "shell: permission denied: %s\n", args[0]);
	return (126);
}

int		exec_pipe(t_pipe_seq *cmd)// here !!
{
	int		pfd[2];
	int		status;
	pid_t	pid_l;
	pid_t	pid_r;


	if (cmd->right == NULL)
		exit(exec_simple_cmd(cmd->left));
	if(pipe(pfd) != 0)
		return (1);
	if ((pid_l = fork()) == -1)
		return (2);//should set errno
	if (pid_l == 0)
	{
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
				exec_pipe(cmd->right);
			else
				exit(exec_simple_cmd(cmd->right->left));
		}
		close(pfd[0]);
		close(pfd[1]);
		waitpid(pid_l, NULL, 0);
		waitpid(pid_r, &status, 0);
		// fprintf(ttt,"child_l:[%d] exit(%d)\n", pid_l, tmp);
		// fprintf(ttt,"child_r:[%d] exit(%d)\n", pid_r, status);
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

void	reset_in_out(int set)
{
	static int in = -1;
	static int out = -1;
	static int err = -1;

	if (set)
	{
		in = dup(STDIN);
		out = dup(STDOUT);
		err = dup(STDOUT);
	}
	else if (in != -1 && out != -1 && err != -1)
	{
		dup2(in, STDIN);
		if (in != STDIN)
			close(in);
		dup2(out, STDOUT);
		if (in != STDOUT)
			close(out);
		dup2(err, STDERR);
		if (in != STDERR)
			close(err);
	}
}

int		exec_no_fork_builtin(t_simple_cmd *cmd, char **av)
{
	int			status;
	t_variable	*tmp;
	char		**env;


	tmp = var_list_dup(g_var.var);
	reset_in_out(SETDFL);
	if (do_prefix(cmd->prefix, tmp, 0) || do_suffix(cmd->suffix))
	{
		//free(tmp)
		reset_in_out(GETDFL);
		return (1);
	}
	env = env_to_tab(tmp, 0);
	//free(tmp);
	status = builtins(av[0], av, env);
	reset_in_out(GETDFL);
	// free(env);
	// free(av);
	return (status);
}

int		exec_no_fork(t_pipe_seq *cmd, int bg)
{
	char		**av;
	int			status;

	if (cmd->right == NULL && !bg)
	{
		av = get_arg_var_sub(cmd->left);
		if (av && is_builtin(av[0]))
			return (exec_no_fork_builtin(cmd->left, av));
		// free(av);
		if (!(cmd->left->name) && !(cmd->left->word))
		{
			reset_in_out(SETDFL);
			status = do_prefix(cmd->left->prefix, g_var.var, 1);
			reset_in_out(GETDFL);
			return (status);
		}
	}
	return (-42);
}

int		exec_ast(t_pipe_seq *cmd, int bg)
{
	int			child;
	int			status;

	if ((status = exec_no_fork(cmd, bg)) != -42)
		return (status << 8);
	status = 0;
	child = fork();
	if (child == 0)
	{
		ft_set_attr(1);
		signal(SIGINT, SIG_DFL);
		// def_io = dup(STDIN);
		exec_pipe(cmd);
	}
	else if (!bg)
	{
		waitpid(child, &status, 0);
		exit_status(status);
		// fprintf(ttt,"P_child:[%d] exit(%d) - (%d)\n", child, WEXITSTATUS(status) , g_var.exit_status);
	}
	else
	{
		// fprintf(ttt, "==++++++not waiting++++++\n");
		add_proc(child);
	}
	return (status);
}

int		execute(t_and_or *cmd, int bg)
{
	int dp;
	int ret = 0;

	while (cmd)
	{
		dp = cmd->dependent;
		if (!dp || (dp == 1 && !g_var.exit_status) || (dp == 2 && g_var.exit_status))
		{
			exit_status(exec_ast(cmd->ast, bg));
			// fprintf(ttt, "===exit stats[%d]===\n", g_var.exit_status);
		}
		cmd = cmd->next;
	}
	return (ret);
}
