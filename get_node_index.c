/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node_index.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 19:07:53 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/22 19:07:54 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "readline.h"

t_hist	*get_node_index(t_hist **current, int index)
{
	t_hist	*node;

	node = *current;
	if (index == 0)
	{
		while (node->next)
			node = node->next;
		return (node);
	}
	while (node)
	{
		if (node->index == index)
		{
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}