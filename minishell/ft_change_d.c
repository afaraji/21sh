/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:46:40 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/01 17:46:42 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_change_d(t_lst *head, char *str1, char *str2)
{
	t_lst	*node;

	if (!head)
		return (1);
	node = head;
	while (node)
	{
		if (ft_strcmp(node->name, str1) == 0)
		{
			free(node->content);
			node->content = ft_strdup(str2);
			return (0);
		}
		node = node->next;
	}
	node = head;
	while (node->next)
		node = node->next;
	if (!(node->next = (t_lst *)malloc(sizeof(t_lst))))
		return (1);
	node = node->next;
	node->name = ft_strdup(str1);
	node->content = ft_strdup(str2);
	node->next = NULL;
	return (0);
}
