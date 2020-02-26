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


void	left_select2(t_line *line, int i)
{
	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	while (line->str[i])
	{
		ft_putchar(line->str[i]);
		i++;
	}
}

void	right_select2(t_line *line)
{
	int i;

	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	i = line->curs;
	while (line->str[i])
	{
		ft_putchar(line->str[i]);
		i++;
	}
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
}

void	left_select(t_line *line, t_select *select)
{
	int i;

	if (line->curs)
	{
		select->len--;
		if (select->len >= 0)
		{
			line->curs--;
			tputs(tgetstr("cd", NULL), 1, ft_intputchar);
			line->curs++;
			right_select2(line);
		}
		else
		{
			//fprintf(ttyfd, "l && len < 0\n");
			tputs(tgetstr("cd", NULL), 1, ft_intputchar);
			tputs(tgetstr("sc", NULL), 1, ft_intputchar);
			i = line->curs;
			ft_putstr("\x1B[35m");
			while (i <= select->start)
			{
				ft_putchar(line->str[i]);
				i++;
			}
			ft_putstr("\x1b[39m");
			left_select2(line , i);
			tputs(tgetstr("rc", NULL), 1, ft_intputchar);
		}
	}
}
/************ fixe problem when select in the second line for multiline**********/
void	right_select(t_line *line, t_select *select)
{
	int i;

	if (line->str[line->curs])
	{
		if (select->len >= 0)
		{
			tputs(tgetstr("cd", NULL), 1, ft_intputchar);
			ft_putstr("\e[45m");
			ft_putchar(line->str[line->curs]);
			ft_putstr("\e[0m");
			line->curs++;
			right_select2(line);
			go_left(line);
			// tputs(tgetstr("cd", NULL), 1, ft_intputchar);
			// i = select->start;
			// while (line->curs > i)
			// 	go_left(line);
			// ft_putstr("\x1B[35m");
			// while (i <= select->start + select->len)
			// {
			// 	sleep(1);
			// 	ft_putchar(line->str[i]);
			// 	line->curs++;
			// 	i++;
			// }
			// ft_putstr("\x1b[39m");
			// right_select2(line , i);
			// sleep(1);
			// go_left(line);
		}
		else
		{
			//fprintf(ttyfd, "r && len < 0\n");
			tputs(tgetstr("cd", NULL), 1, ft_intputchar);
			tputs(tgetstr("sc", NULL), 1, ft_intputchar);
			ft_putchar(line->str[line->curs]);
			i = line->curs + 1;
			ft_putstr("\x1B[35m");
			while (i <= select->start)
			{
				ft_putchar(line->str[i]);
				i++;
			}
			ft_putstr("\x1b[39m");
			left_select2(line , i);
			tputs(tgetstr("rc", NULL), 1, ft_intputchar);
		}
		select->len++;
	}
}

void	move_curs(t_line *line, int buff, t_select *select)
{
	if (buff == LFTARROW)
	{
		if (select->on)
		 	left_select(line, select);
		go_left(line);
	}
	else if (buff == RTARROW)
	{
		if (select->on)
			right_select(line, select);
		go_right(line);
	}
	else
	{
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
}
