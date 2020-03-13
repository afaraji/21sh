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
#include "run_cmd.c"

FILE	*ttt;

static int child = 0;

void	ft_close(int fd)
{
	if (close(fd) == -1)
	{
		fprintf(stderr, "close: error closing fd: %d\n", fd);
	}
}

void	report_error_and_exit(const char* msg)
{
	perror(msg);
	(child ? _exit : exit)(EXIT_FAILURE);
}

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
	return (paths);
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

t_io_list	*get_io_redirect(t_cmd_prefix *prefix, t_cmd_suffix *suffix)
{
	t_io_list	*head = NULL;
	t_io_list	*node;

	while (prefix)
	{
		if (prefix->io_redirect)
		{
			if (!head)
			{
				node = (t_io_list *)malloc(sizeof(t_io_list));
				node->node = prefix->io_redirect;
				node->next = NULL;
				head = node;
			}
			else
			{
				node->next = (t_io_list *)malloc(sizeof(t_io_list));
				node = node->next;
				node->node = prefix->io_redirect;
				node->next = NULL;
			}
		}
		prefix = prefix->prefix;
	}
	while (suffix)
	{
		if (suffix->io_redirect)
		{
			if (!head)
			{
				node = (t_io_list *)malloc(sizeof(t_io_list));
				node->node = prefix->io_redirect;
				node->next = NULL;
				head = node;
			}
			else
			{
				node->next = (t_io_list *)malloc(sizeof(t_io_list));
				node = node->next;
				node->node = prefix->io_redirect;
				node->next = NULL;
			}
		}
		suffix = suffix->suffix;
	}
	return (head);
}

t_variable	*get_ass_word(t_cmd_prefix *prefix)//not sure if it works without malloc
{
	t_variable	*head = NULL;
	t_variable	*node;

	while (prefix)
	{
		if (prefix->ass_word)
		{
			if (!head)
			{
				node = prefix->ass_word;
				head = node;
			}
			else
			{
				node->next = prefix->ass_word;
				node = node->next;
			}
		}
		prefix = prefix->prefix;
	}
	return (head);
}

char	**get_argv(char *cmd, t_cmd_suffix *suffix)
{
	char			**args;
	t_cmd_suffix	*node;
	int				i;

	if (!cmd)
		return (NULL);
	node = suffix;
	i = 0;
	while (node)
	{
		if (node->word)
			i++;
		node = node->suffix;
	}
	args = (char **)malloc(sizeof(char *) * (i + 2));
	args[0] = ft_strdup(cmd);
	i = 1;
	while (suffix)
	{
		if (suffix->word)
		{
			args[i] = ft_strdup(suffix->word);
			i++;
		}
		suffix = suffix->suffix;
	}
	return (args);
}

int		exec_simple_cmd(t_simple_cmd *cmd)
{
	t_io_list		*io;
	t_variable		*var_list;
	char			**argv;
	int				ret;

	if (cmd->prefix)
	{
		// get all (io_redirects from: prefix[i]->io_redirect && suffix[i]->io_redirect) and/or (ass_words: prefix->assword)
		// get cmd_path from cmd->word
		// get cmd_args from suffix[i]->word
		io = get_io_redirect(cmd->prefix, cmd->suffix);
		var_list = get_ass_word(cmd->prefix);
		argv = get_argv(cmd->word, cmd->suffix);
	}
	else if (cmd->name)
	{
		// get all (io_redirects from: suffix[i]->io_redirect)
		// get cmd_path from cmd->name
		// get cmd_args from suffix[i]->word
		io = get_io_redirect(NULL, cmd->suffix);
		var_list = NULL;
		argv = get_argv(cmd->name, cmd->suffix);
	}
	else
	{
		// error !! setup errno
		return (80);
	}
	//setup io redirections
	ret = run_cmd(argv);
	if (!ret && var_list)
	{
		//insert variable with env = 1
		return (0);
	}
	return (ret);
}

int		exec_ast(t_pipe_seq *cmd, int in_fd)
{
	int		s_in;
	int		s_out;
	int		s_err;
	int		fd[2];
	int		ch_pid;

	s_in = dup(0);
	s_out = dup(1);
	s_err = dup(2);
	if (!cmd->right)
	{// last cmd
		redirect(in_fd, STDIN_FILENO);
		//exec ?
	}
	else
	{
		if (pipe(fd) == -1)
		{
			return (-1);//should set errno
		}
		if ((ch_pid = fork()) == -1)
			return (-1);//should set errno
		if (ch_pid == 0)
		{
			// child
			child = 1;
			ft_close(fd[0]);
			redirect(in_fd, STDIN);  /* read from in_fd */
			redirect(fd[1], STDOUT); /* write to fd[1] */
			exec_simple_cmd(cmd->left);
			return (-1); // should set errno
		}
		else
		{
			// parent
			ft_close(fd[1]);
			ft_close(in_fd);
			exec_ast(cmd->right, fd[0]);
		}
		
	}
	
	// current cmd setup
	exec_simple_cmd(cmd->left);
	// some next cmd setup
	exec_ast(cmd->right, 0);

	return (0);
}

int		execute(t_and_or *cmd, int bg)
{
	ttt = fopen("/dev/ttys004", "w");
	int dp;
	int ret = 0;
	int child_pid;

	// need to fork here
	if ((child_pid = fork()) == -1)
		return (10);	// should set g_var.errno
	if (child_pid == 0)
	{
		dp = cmd->dependent;
		while (cmd)
		{
			if (!dp || (dp == 1 && !g_var.exit_status) || (dp == 2 && g_var.exit_status))
			{
				fprintf (ttt, "++++++++++++ andor_cmd [bg:%d]+++++++++++", bg);
				
				ret = exec_ast(cmd->ast, STDIN);
				g_var.exit_status = ret;
			}
			cmd = cmd->next;
		}
	}
	if (child_pid && !bg)
	{
		waitpid(child_pid, NULL, 0); // should it be &ret instead of NULL to get exitstatus of child ?
	}
	return (ret);
}
