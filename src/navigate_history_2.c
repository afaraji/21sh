/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate_history_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:00:25 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/08 18:00:27 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

void	freeleak_down_2(t_terminal *term, char *old_line)
{
	char	*tmp;

	ft_strdel(&(term->line->str));
	tmp = ft_strdup(old_line);
	free(term->line->str);
	term->line->str = tmp;
}

void	freeleak_up_down(t_terminal *term, t_hist *to_print)
{
	char	*tmp;

	ft_strdel(&(term->line->str));
	tmp = ft_strdup(to_print->hist_str);
	free(term->line->str);
	term->line->str = tmp;
}

void	move_curs_right(t_line *line)
{
	while (line->str[line->curs])
	{
		if (line->init_pos < line->row)
		{
			line->init_pos--;
			go_right(line);
		}
		else
			line->curs++;
	}
}

void	hist_up_down(t_terminal **term, t_hist **current)
{
	t_hist	*to_print;

	to_print = get_node_index(current, (*term)->index);
	del_line((*term)->line);
	(*term)->index = to_print->index;
	freeleak_up_down(*term, to_print);
	if ((*term)->line->init_pos == (*term)->line->row)
		display_line_from_begin((*term)->line);
	else
		display_line((*term)->line);
	move_curs_right((*term)->line);
	(*term)->line->curs = ft_strlen(to_print->hist_str);
}
