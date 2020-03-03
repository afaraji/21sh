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

void	get_cmd(t_line *line, char buff, t_hist **his_head)
{
	line->str = join_line(line->str, buff, line->curs);
	display_line(line);
	go_right(line);
	if (buff == ENTER)
	{
		line->str = trim_cmd(line->str);
		if (ft_strcmp(line->str, "") != 0)
			add_cmd_to_his_list(line->str, his_head);
	}
}

void	printable_2(t_line *line, t_select *select)
{
	select->on = 0;
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	display_line_from_begin(line);
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
}

int		printable(t_line *line, t_hist **his_head, t_select *select, int buff)
{
	int	curs;

	if ((ft_isprint(buff) || buff == ENTER))
	{
		if (select->on == 1)
			printable_2(line, select);
		else
		{
			get_cmd(line, buff, his_head);
			if (buff == ENTER)
			{
				curs = line->curs;
				while (curs <= (int)ft_strlen(line->str))
				{
					go_right(line);
					curs++;
				}
				return (1);
			}
		}
	}
	return (0);
}
