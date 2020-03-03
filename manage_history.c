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

#include "readline.h"

char	*tmp_strdup(char *str)
{
	char	*s;
	int		i;

	s = ft_strdup(str);
	i = 0;
	while (s[i])
	{
		if (s[i] == '#')
			s[i] = '\n';
		i++;
	}
	return (s);
}

t_hist	*get_his_node(char *file_str, t_hist *prec, int i)
{
	t_hist	*node;

	node = (t_hist *)malloc(sizeof(t_hist));
	node->hist_str = tmp_strdup(file_str);
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

void	add_cmd_to_his_list(char *cmd, t_hist **his_head)
{
	t_hist	*node;
	int		i;

	if (!(*his_head))
	{
		i = 1;
		get_his_list(cmd, his_head, i++);
	}
	else
	{
		node = *his_head;
		while (node->next)
		{
			node = node->next;
		}
		node->next = get_his_node(cmd, node, node->index + 1);
	}
}

int		save_list(t_hist *his_head)
{
	t_hist	*node;
	int		fd;

	node = his_head;
	if (!(fd = open("./.myshell_history", O_WRONLY)))
		return (-1);
	while (node)
	{
		ft_putstr_fd(node->hist_str, fd);
		ft_putchar_fd('\n', fd);
		node = node->next;
	}
	close(fd);
	return (0);
}
