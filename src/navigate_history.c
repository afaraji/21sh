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

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

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

void	history_up(t_terminal *term, t_hist **current)
{
	if (term->index == 0)
	{
		hist_up_down(&term, current);
	}
	else if (term->index - 1 > 0)
	{
		(term->index)--;
		hist_up_down(&term, current);
	}
}

void	history_down(t_terminal *term, t_hist **current, char *old_line)
{
	int		last;

	last = (get_node_index(current, 0))->index;
	if (term->index + 1 <= last && term->index)
	{
		(term->index)++;
		hist_up_down(&term, current);
	}
	else if (term->index == last)
	{
		del_line(term->line);
		freeleak_down_2(term, old_line);
		if (term->line->init_pos == term->line->row)
			display_line_from_begin(term->line);
		else
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
