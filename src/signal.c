/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
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
	pid = waitpid(0, &status, WNOWAIT);
	while (proc)
	{
		if (proc->ppid == pid)
		{
			proc->status = status;
			waitpid(pid, &status, 0);
			proc->done = 1;
			return ;
		}
		proc = proc->next;
	}
	(void)signum;
}

void		ft_signal(void)
{
	signal(SIGINT, &signal_callback_handler);
	signal(SIGCHLD, &child_handler);
}
