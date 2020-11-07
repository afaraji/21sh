/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:03:19 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/07 16:03:26 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

t_hist	*get_his_node(char *file_str, t_hist *prec, int i)
{
	t_hist	*node;

	if (!(node = (t_hist *)malloc(sizeof(t_hist))))
		return (NULL);
	node->hist_str = ft_strdup(file_str);
	node->index = i;
	node->next = NULL;
	node->prec = prec;
	return (node);
}

void	get_his_list(char *file_str, t_hist **head, int index)
{
	t_hist	*node;

	if (!(*head))
	{
		node = get_his_node(file_str, NULL, index);
		*head = node;
	}
	else
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = get_his_node(file_str, node, index);
	}
}

void	add_cmd_to_hislist_1(char *cmd, int mult_line, t_hist **his_head)
{
	t_hist	*node;
	char	*tmp;

	node = *his_head;
	while (node->next)
		node = node->next;
	if (mult_line == 0 || mult_line == -1)
		node->next = get_his_node(cmd, node, node->index + 1);
	else
	{
		tmp = ft_strjoin(node->hist_str, "\n");
		free(node->hist_str);
		node->hist_str = ft_strjoin(tmp, cmd);
		free(tmp);
	}
}

void	add_cmd_to_his_list(char *cmd, t_hist **his_head, int mult_line)
{
	int		i;

	if (mult_line == SMLSML)
		return ;
	if (!(*his_head))
	{
		i = 1;
		get_his_list(cmd, his_head, i++);
	}
	else
	{
		add_cmd_to_hislist_1(cmd, mult_line, his_head);
	}
}

int		save_list(void)
{
	t_hist	*node;
	int		fd;

	node = g_var.history;
	if ((fd = open(HIST_FILE, O_WRONLY)) == -1)
	{
		ft_print(STDERR, "couldn't save history list.\n");
		return (-1);
	}
	while (node)
	{
		ft_putstr_fd(node->hist_str, fd);
		ft_putchar_fd('\n', fd);
		node = node->next;
	}
	close(fd);
	return (0);
}
