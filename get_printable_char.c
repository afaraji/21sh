/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_printable_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:03:32 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/04 00:03:34 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	get_cmd(t_terminal *term, t_hist **his_head)
{
	char	*tmp;

	term->line->str = join_line(term->line->str, term->buff, term->line->curs);
	display_line(term->line);
	go_right(term->line);
	if (term->buff == ENTER)
	{
		tmp = term->line->str;
		term->line->str = trim_cmd(term->line->str);
		ft_strdel(&tmp);
		if (ft_strcmp(term->line->str, "") != 0)
			add_cmd_to_his_list(term->line->str, his_head);
	}
}

void	printable_2(t_terminal *term)
{
	term->select->on = 0;
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	display_line_from_begin(term->line);
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
}

int		printable(t_terminal *term, t_hist **his_head)
{
	int	curs;

	if ((ft_isprint(term->buff) || term->buff == ENTER))
	{
		if (term->select->on == 1)
			printable_2(term);
		else
		{
			get_cmd(term, his_head);
			if (term->buff == ENTER)
			{
				curs = term->line->curs;
				while (curs <= (int)ft_strlen(term->line->str))
				{
					go_right(term->line);
					curs++;
				}
				return (1);
			}
		}
	}
	return (0);
}
