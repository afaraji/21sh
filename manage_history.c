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

t_hist	*get_his_node(char *file_str, t_hist *prec)
{
	t_hist	*node;

	node = (t_hist *)malloc(sizeof(t_hist));
	node->hist_str = file_str;
	node->next = NULL;
	node->prec = prec;
	return(node);	
}

void	get_his_list(char *file_str, t_hist **head)
{
	t_hist	*node;

	if (!(*head))
	{
		node = get_his_node(file_str, NULL);
		*head = node;
	}
	else
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = get_his_node(file_str, node);
	}
	
}

void	add_cmd_to_his_list(char *cmd, t_hist **his_head)
{
	t_hist	*node;
	int		i;

	node = *his_head;
	while (node->next)
	{
		node = node->next;
	}
	i = 0;
	while (cmd[i])
		i++;
	node->next = get_his_node(cmd, node);
}

void	save_list(t_hist *his_head, int fd)
{
	t_hist	*node;

	node = his_head;
	while (node)
	{
		ft_putstr_fd(node->hist_str, fd);
		ft_putchar_fd('\n', fd);
		node = node->next;
	}
}
