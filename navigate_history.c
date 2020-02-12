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
		{
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}

void	navigate_history_2(t_line *line, t_hist **current, int *index)
{
	t_hist	*to_print;

	if (*index == 0)
	{
		to_print = get_node_index(current, *index);
		del_line(line);
		*index = to_print->index;
		ft_strdel(&line->str);
		line->str = ft_strdup(to_print->hist_str);
		ft_putstr_fd(line->str, 1);
		line->curs = ft_strlen(to_print->hist_str);
	}
	else if (*index - 1 > 0)
	{
		(*index)--;
		to_print = get_node_index(current, *index);
		del_line(line);
		ft_strdel(&line->str);
		line->str = ft_strdup(to_print->hist_str);
		ft_putstr(line->str);
		line->curs = ft_strlen(to_print->hist_str);
	}
}

void	navigate_history_3(t_line *line, t_hist **curr, int *i, char *old_line)
{
	t_hist	*to_print;
	int		last;

	last = (get_node_index(curr, 0))->index;
	if (*i + 1 <= last && *i)
	{
		(*i)++;
		to_print = get_node_index(curr, *i);
		del_line(line);
		ft_strdel(&line->str);
		line->str = ft_strdup(to_print->hist_str);
		ft_putstr(line->str);
		line->curs = ft_strlen(to_print->hist_str);
	}
	else if (*i == last)
	{
		del_line(line);
		ft_strdel(&line->str);
		line->str = ft_strdup(old_line);
		ft_putstr(line->str);
		line->curs = ft_strlen(old_line);
		(*i)++;
	}
}

void	navigate_history(t_line *line, int buff, t_hist **current, int *index)
{
	static char *old_line = NULL;

	if (*index == 0 || *index == (get_node_index(current, 0))->index + 1)
		old_line = ft_strdup(line->str);
	if (buff == UPARROW)
		navigate_history_2(line, current, index);
	else if (buff == DWNARROW)
		navigate_history_3(line, current, index, old_line);
}
