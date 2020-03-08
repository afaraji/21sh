/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 20:53:44 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/12 20:53:45 by sazouaka         ###   ########.fr       */
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
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	navigate_history(t_terminal *term, t_hist **current)
{
	static char *old_line = NULL;

	if (*current)
	{
		if (term->index == 0
		|| term->index == (get_node_index(current, 0))->index + 1)
		{
			if (old_line)
				free(old_line);
			old_line = ft_strdup(term->line->str);
		}
		if (term->buff == UPARROW)
			history_up(term, current);
		else if (term->buff == DWNARROW)
			history_down(term, current, old_line);
	}
}
