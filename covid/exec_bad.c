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

FILE	*ttt;

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

	if (!access(str, X_OK))
	{
		return (ft_strdup(str));
	}
	paths = paths_from_env();
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], str);
		if (!access(tmp, X_OK))
		{
			return (tmp);
		}
		free(tmp);
		i++;
	}
	return(NULL);
}

int		env_tab_count(void)
{
	t_variable	*node;
	int			count;
	
	node = g_var.var;
	count = 0;
	while (node)
	{
		if (node->env == 0)
			count++;
		node = node->next;
	}
	return (count);
}

char	**env_to_tab(void)
{
	t_variable	*node;
	char		**argv;
	char		*tmp;
	int			i;
	
	node = g_var.var;
	i = env_tab_count();	
	if (!(argv = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (node)
	{
		if (node->env == 0)
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
	t_simple_lst	*args;
	t_simple_lst	*tmp;

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


int		exec_simple_cmd(t_simple_cmd *cmd)
{
	char	**args;
	char	**env;
	char	*cmd_path;
	t_simple_lst	*args_list;
	t_variable	*vars;
	
	if (!cmd)
		return (42);
	do_simpleCmd(cmd);//does prefix and suffix
	args = get_args(cmd);
	if (!args)
	{
		//do word assignement perma
		return (0);
	}
	// if builtin exec builtin
	if (is_builtin(args[0]))
	{
		//do builtin
		return (builtins(args[0], args));
	}
	cmd_path = get_cmdpath(args[0]);
	env = env_to_tab();
	ft_set_attr(1);
	if (execve(cmd_path, args, env) == -1)//error handling
		printf("%s:ErRoR exxecve\n",cmd_path);
	perror("PERROR");
	return (1);
}

int		exec_ast(t_pipe_seq *cmd)
{
	int		pfd[2];
	int		status, status2;
	pid_t	pid_l;
	pid_t	pid_r;


	if (cmd->right == NULL)
	{
		exec_simple_cmd(cmd->left);
		return (0);
		// exit(return_value) ?? should exit or not ?
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
			exec_ast(cmd->right);
		}
		else
		{
			exit(exec_simple_cmd(cmd->right->left));
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
			exit(exec_simple_cmd(cmd->left));
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

int		do_assignement(t_cmd_prefix *pref, t_variable *head)
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
			while (tmp)
			{
				if (!ft_strcmp(tmp->key, node->ass_word->key))
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
			tmp = head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = var_dup(node->ass_word);
		}
		node = node->prefix;
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
		node = node->next;
	}
	return (head);
}

int		do_left(t_simple_cmd *cmd, int in,int out, int bg)
{
	char	**av;
	char	**env;
	pid_t	child;
	int		status;

	if (cmd->prefix)
	{
		if (cmd->word == NULL)
		{
			do_assignement(cmd->prefix, g_var.var);
		}
		else
		{
			// ass only for cmd->word
			// is builtin ??
			//fork? and do_simpleCmd then execve
			t_variable *tmp;
			tmp = var_list_dup(g_var.var);
			do_assignement(cmd->prefix, tmp);
			av = get_args(cmd);
			ft_set_attr(1);
			env = env_to_tab();
			if (is_builtin(cmd->name))
			{
				builtins(av[0], av);	
			}
			else
			{
				child = fork();
				if (child == 0)
				{
					execve(get_cmdpath(av[0]), av, env);
					perror("error in [1]:");
				}
				else if (!bg)
				{
					waitpid(child, &status, 0);
				}
			}
		}
	}
	else if (cmd->name)
	{
		if (cmd->suffix)
		{
			do_suffix(cmd->suffix);
		}
		av = get_args(cmd);
		ft_set_attr(1);
		env = env_to_tab();
		if (is_builtin(cmd->name))
		{
			builtins(av[0], av);	
		}
		else
		{
			child = fork();
			if (child == 0)
			{
				execve(get_cmdpath(av[0]), av, env);
				perror("error in [1]:");
			}
			else if (!bg)
			{
				waitpid(child, &status, 0);
			}
		}
	}
	return (0);
}

int		exec_pipe(t_pipe_seq *cmd, int bg)
{
	int		pfd[2];
	t_pipe_seq *node;

	node = cmd;
	while (node->right)
	{
		if(!pipe(pfd))
			return (1);
		do_left(node->left, STDIN,pfd[1], bg);
		do_right(node->right, pfd[0], STDOUT, bg);
		close(pfd[0]);
		close(pfd[1]);
		node = node->right;
	}
	

}

int		execute(t_and_or *cmd, int bg)
{
	ttt = fopen("/dev/ttys004", "w");
	int dp;
	int ret = 0;
	int child_pid;

	while (cmd)
	{
		dp = cmd->dependent; // or should be dp = cmd->next->dependent;
		if (!dp || (dp == 1 && !g_var.exit_status) || (dp == 2 && g_var.exit_status))
		{
			// ret = exec_ast(cmd->ast);// here should go exec_pipe();
			ret = exec_pipe(cmd->ast, bg);
			g_var.exit_status = ret;
		}
		cmd = cmd->next;
	}
	return (ret);
}
