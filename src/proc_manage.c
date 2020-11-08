/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:49:31 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 17:49:48 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

char	*last_in_hist(void)
{
	t_hist	*node;

	node = g_var.history;
	while (node->next)
		node = node->next;
	if (node->hist_str)
		return (ft_strdup(node->hist_str));
	return (ft_strdup(""));
}

void	add_proc(pid_t pid)
{
	t_proc	*node;

	node = g_var.proc;
	while (node->next)
		node = node->next;
	node->next = (t_proc *)malloc(sizeof(t_proc));
	node->next->ppid = pid;
	node->next->index = node->index + 1;
	node->next->done = 0;
	node->next->status = -1;
	node->next->str = last_in_hist();
	node->next->next = NULL;
	ft_putstr("[");
	ft_putnbr(node->next->index);
	ft_putstr("] ");
	ft_putnbr(pid);
	ft_putstr("\n");
}

void	delet_proc(pid_t pid)
{
	t_proc	*node;
	t_proc	*old_node;

	node = g_var.proc;
	old_node = NULL;
	while (node)
	{
		if (pid == node->ppid)
		{
			ft_strdel(&(node->str));
			old_node->next = node->next;
			free(node);
			break ;
		}
		old_node = node;
		node = node->next;
	}
}

void	bg_jobs(void)
{
	t_proc	*proc;

	proc = g_var.proc;
	while (proc)
	{
		if (proc->done == 1)
		{
			ft_print(STDOUT, "\n[%d]\tDone\t\t%s\n", proc->index, proc->str);
			delet_proc(proc->ppid);
		}
		proc = proc->next;
	}
}
