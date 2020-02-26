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

void	move_curs_right(t_line *line)
{
	while (line->str[line->curs])
	{
		go_right(line);
	}
}

void	history_up(t_line *line, t_hist **current, int *index)
{
	t_hist	*to_print;

	if (*index == 0)
	{
		to_print = get_node_index(current, *index);
		del_line(line);
		*index = to_print->index;
		ft_strdel(&line->str);
		line->str = ft_strdup(to_print->hist_str);
		display_line(line);
		move_curs_right(line);
		line->curs = ft_strlen(to_print->hist_str);
	}
	else if (*index - 1 > 0)
	{
		(*index)--;
		to_print = get_node_index(current, *index);
		del_line(line);
		ft_strdel(&line->str);
		line->str = ft_strdup(to_print->hist_str);
		display_line(line);
		move_curs_right(line);
		line->curs = ft_strlen(to_print->hist_str);
	}
}

void	history_down(t_line *line, t_hist **curr, int *i, char *old_line)
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
		display_line(line);
		move_curs_right(line);
		line->curs = ft_strlen(to_print->hist_str);
	}
	else if (*i == last)
	{
		del_line(line);
		ft_strdel(&line->str);
		line->str = ft_strdup(old_line);
		display_line(line);
		move_curs_right(line);
		line->curs = ft_strlen(old_line);
		(*i)++;
	}
}

void	navigate_history(t_line *line, int buff, t_hist **current, int *index)
{
	static char *old_line = NULL;

	if (*current)
	{
		if (*index == 0 || *index == (get_node_index(current, 0))->index + 1)
			old_line = ft_strdup(line->str);
		if (buff == UPARROW)
			history_up(line, current, index);
		else if (buff == DWNARROW)
			history_down(line, current, index, old_line);
	}
}
