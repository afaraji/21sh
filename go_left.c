/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_left.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:48:41 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/20 14:48:42 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	go_upline(t_line *line)
{
	tputs(tgetstr("up", NULL), 1, ft_intputchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, line->col - 1), 1, ft_intputchar);
}

void	go_left_2(t_line *line)
{
	int	tmp;

	tmp = len_str_from_nl(line, line->curs - 1);
	if (tmp == 0)
		tputs(tgetstr("up", NULL), 1, ft_intputchar);
	else
	{
		tmp = tmp % line->col;
		if (tmp == 0)
		{
			tmp = line->col;
			line->curs--;
		}
		tputs(tgetstr("up", NULL), 1, ft_intputchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, tmp), 1, ft_intputchar);
	}
}

void	go_left_3(t_line *line, int len)
{
	if (len % line->col == 0)
		go_upline(line);
	else
		tputs(tgetstr("le", NULL), 1, ft_intputchar);
}

void	go_left(t_line *line)
{
	int len;

	if (line->curs > 0)
	{
		if (is_multline(line->str))
		{
			len = len_str_from_nl(line, line->curs);
			if (len == 0)
				go_left_2(line);
			else
				go_left_3(line, len);
		}
		else
		{
			if (((line->curs + line->pmt_s - 1) % line->col) == 0)
				go_upline(line);
			else
				tputs(tgetstr("le", NULL), 1, ft_intputchar);
		}
		line->curs--;
	}
}
