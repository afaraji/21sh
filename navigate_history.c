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

void	history_up(t_terminal *term, t_hist **current)
{
	t_hist	*to_print;

	if (term->index == 0)
	{
		to_print = get_node_index(current, term->index);
		del_line(term->line);
		term->index = to_print->index;
		ft_strdel(&(term->line->str));
		term->line->str = ft_strdup(to_print->hist_str);
		display_line(term->line);
		move_curs_right(term->line);
		term->line->curs = ft_strlen(to_print->hist_str);
	}
	else if (term->index - 1 > 0)
	{
		(term->index)--;
		to_print = get_node_index(current, term->index);
		del_line(term->line);
		ft_strdel(&(term->line->str));
		term->line->str = ft_strdup(to_print->hist_str);
		display_line(term->line);
		move_curs_right(term->line);
		term->line->curs = ft_strlen(to_print->hist_str);
	}
}

void	history_down(t_terminal *term, t_hist **current, char *old_line)
{
	t_hist	*to_print;
	int		last;

	last = (get_node_index(current, 0))->index;
	if (term->index + 1 <= last && term->index)
	{
		(term->index)++;
		to_print = get_node_index(current, term->index);
		del_line(term->line);
		ft_strdel(&(term->line->str));
		term->line->str = ft_strdup(to_print->hist_str);
		display_line(term->line);
		move_curs_right(term->line);
		term->line->curs = ft_strlen(to_print->hist_str);
	}
	else if (term->index == last)
	{
		del_line(term->line);
		ft_strdel(&(term->line->str));
		term->line->str = ft_strdup(old_line);
		display_line(term->line);
		move_curs_right(term->line);
		term->line->curs = ft_strlen(old_line);
		(term->index)++;
	}
}

void	navigate_history(t_terminal *term, t_hist **current)
{
	static char *old_line = NULL;

	if (*current)
	{
		if (term->index == 0
		|| term->index == (get_node_index(current, 0))->index + 1)
			old_line = ft_strdup(term->line->str);
		if (term->buff == UPARROW)
			history_up(term, current);
		else if (term->buff == DWNARROW)
			history_down(term, current, old_line);
	}
}
