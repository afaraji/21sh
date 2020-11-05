/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:00:18 by sazouaka          #+#    #+#             */
/*   Updated: 2020/10/29 23:56:26 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

t_hist		*create_history(void)
{
	char	*file_str;
	t_hist	*his_list;
	int		fd;
	int		i;

	his_list = NULL;
	if (!(fd = open("./.myshell_history", O_RDONLY | O_CREAT, 0600)))
		return (NULL);
	i = 1;
	while (get_next_line(fd, &file_str) == 1)
	{
		get_his_list(file_str, &his_list, i++);
		ft_strdel(&file_str);
	}
	close(fd);
	return (his_list);
}

int			is_number(char *str)
{
	if (!str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	return (is_all_digits(str));
}

int			ft_exit(char **av)
{
	int		status;

	ft_set_attr(1);
	save_list();
	free_g_var();
	if (av[1])
	{
		if (ft_strlen(av[1]) < 10 && is_number(av[1]))
		{
			status = ft_atoi(av[1]);
			if (av[2])
				ft_print(STDERR, "exit\nshell: exit: too many arguments.\n");
		}
		else
		{
			status = 255;
			ft_print(STDERR, "exit\nshell: exit: ");
			ft_print(STDERR, "%s: numeric argument required.\n", av[1]);
		}
	}
	else
		status = 0;
	exit(status);
}

t_variable	*get_env(char *s, int typ)
{
	t_variable	*node;
	int			i;

	i = 0;
	node = (t_variable *)malloc(sizeof(t_variable));
	node->next = NULL;
	node->env = typ;
	while (s && s[i] && s[i] != '=')
		i++;
	node->key = ft_strsub(s, 0, i);
	node->value = ft_strdup(&s[i + 1]);
	node->next = NULL;
	return (node);
}

t_variable	*get_setvar(void)
{
	char		*tmp1;
	char		*tmp2;
	t_variable	*head;

	head = get_env("!=0", 2);
	head->next = get_env("#=0", 2);
	tmp1 = ft_itoa(getpid());
	tmp2 = ft_strjoin("$=", tmp1);
	head->next->next = get_env(tmp2, 2);
	free(tmp1);
	free(tmp2);
	head->next->next->next = get_env("?=0", 2);
	return (head);
}

t_variable	*get_set(char **env)
{
	t_variable	*head;
	t_variable	*node;
	int			i;

	head = get_setvar();
	node = head;
	while (node->next)
		node = node->next;
	i = 0;
	while (env && env[i])
	{
		node->next = get_env(env[i], 0);
		node = node->next;
		i++;
	}
	return (head);
}

void		get_ppid_list(void)
{
	g_var.proc = (t_proc *)malloc(sizeof(t_proc));
	g_var.proc->ppid = getpid();
	g_var.proc->index = 0;
	g_var.proc->done = 0;
	g_var.proc->status = 0;
	g_var.proc->str = NULL;
	g_var.proc->next = NULL;
}

int			init_shell(char **env)
{
	g_var = (t_shell_var){0, 0, 0, NULL, NULL, NULL, NULL};
	g_var.var = get_set(env);
	g_var.history = create_history();
	get_ppid_list();
	return (0);
}

void		signal_callback_handler(int signum)
{
	if (signum == 2)
	{
		ft_putchar('\n');
		g_var.sig = signum;
		ft_set_attr(0);
	}
	else
		ft_exit(NULL);
}

void		child_handler(int signum)
{
	pid_t	pid;
	int		status;
	t_proc	*proc;

	proc = g_var.proc;
	pid = wait(&status);
	while (proc)
	{
		if (proc->ppid == pid)
		{
			proc->status = status;
			proc->done = 1;
			return ;
		}
		proc = proc->next;
	}
	exit_status(status);
	(void)signum;
}

void		ft_signal(void)
{
	signal(SIGINT, &signal_callback_handler);
	// signal(SIGCHLD, &child_handler);
}

int			main(int ac, char **av, char **env)
{
	char	*line;
	int		ret;

	if (!ttyname(0) || !ttyname(1) || !ttyname(2))
		return (-1);
	line = NULL;
	ret = 0;
	ft_signal();
	if (init_shell(env))
		return (1);
	while (1)
	{
		if (ft_set_attr(0))
			return (1);
		line = readline(0);
		if (ft_strcmp(line, "") && (ret = main_parse(line)))
			exit_status(ret << 8);
		if (line)
			ft_strdel(&line);
		bg_jobs();
	}
	(void)ac;
	(void)av;
	return (0);
}
