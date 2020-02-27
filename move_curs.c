/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_curs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 22:30:54 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/12 22:30:56 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	move_curs(t_line *line, int buff, t_select *select)
{
	if (select->on == 1)
	{
		select->on = 0;
		tputs(tgetstr("sc", NULL), 1, ft_intputchar);
		display_line_from_begin(line);
		tputs(tgetstr("rc", NULL), 1, ft_intputchar);
	}
	if (buff == DEL)
		del_char(line);
	else if (buff == HOME)
		go_home(line);
	else if (buff == END)
		go_end(line);
	else if (buff == UPLINE)
		go_up(line);
	else if (buff == DWNLINE)
		go_down(line);
}
