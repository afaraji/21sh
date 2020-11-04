/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 19:33:46 by sazouaka          #+#    #+#             */
/*   Updated: 2020/10/02 19:33:48 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int				get_node_sum(t_l *head)
{
	int	sum;
	t_l	*node;

	sum = 0;
	node = head;
	while (node)
	{
		sum++;
		node = node->next;
	}
	return (sum);
}

t_l				*sort_list(t_l *head)
{
	t_l		*node1;
	t_l		*node2;
	char	*tmp;

	node1 = head;
	tmp = NULL;
	while (node1->next)
	{
		node2 = node1->next;
		while (node2)
		{
			if (ft_strcmp(node1->data, node2->data) > 0)
			{
				tmp = node1->data;
				node1->data = node2->data;
				node2->data = tmp;
			}
			node2 = node2->next;
		}
		node1 = node1->next;
	}
	return (head);
}

char			**tab_from_list(t_l *head)
{
	t_l		*node;
	char	**tabl;
	int		sum;

	node = head;
	sum = get_node_sum(head);
	tabl = NULL;
	if (!(tabl = (char **)malloc(sizeof(char *) * (sum + 1))))
		return (NULL);
	node = head;
	sum = 0;
	while (node)
	{
		if (!(node->next) || ft_strcmp(node->data, node->next->data))
		{
			tabl[sum] = ft_strdup(node->data);
			sum++;
		}
		node = node->next;
	}
	tabl[sum] = NULL;
	return (tabl);
}
