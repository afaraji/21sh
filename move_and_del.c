/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 22:15:42 by sazouaka          #+#    #+#             */
/*   Updated: 2020/01/17 22:15:48 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		verify_new_line(t_line *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < line->curs)
	{
		if (line->str[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

int		left_newline(t_line *line)
{
	int j;
	int count;
	j = 0;
	count = 0;
	while (j < (*line).curs)
	{
		count++;
		if ((*line).str[j] == '\n')
			count = 0;
		j++;
	}
	if ((count % (*line).col) == 0)
		return (1);
	return (0);
}

int		get_last_newline(t_line *line)
{
	int i;
	int count;

	i = 0;
	while (i < line->curs)
	{
		if (line->str[i] == '\n')
			count = 0;
		i++;
		count++;
	}
	return (count);
}

void	go_upline(t_line *line)
{
	tputs(tgetstr("up", NULL), 1, ft_intputchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, line->col - 1), 1, ft_intputchar);
}

void	move_to_position(t_line *line)
{
	int count;

	count = 0;
	line->curs--;
	count = get_last_newline(line);
	if (count > line->col)
		count = count%line->col;
	if (verify_new_line(line) != 0)
		tputs(tgoto(tgetstr("ch", NULL), 0, count - 1), 1, ft_intputchar);
	else
	{
		if (verify_new_line(line) == 0)
			tputs(tgoto(tgetstr("ch", NULL), 0, (count % line->col ) + line->pmt_s - 1), 1, ft_intputchar);
		else
			tputs(tgoto(tgetstr("ch", NULL), 0, count + line->pmt_s - 1), 1, ft_intputchar);
	}
	line->curs++;
}

void	go_left_2(t_line *line)
{
	if(line->str[line->curs - 1] == '\n')
	{
		go_upline(line);
		move_to_position(line);
	}
	else if (left_newline(line) == 1)
		go_upline(line);
	else
		tputs(tgetstr("le", NULL), 1, ft_intputchar);
}

void	go_left(t_line *line)
{
	if (line->curs > 0)
	{
		if (verify_new_line(line) == 0)
		{
			if (((line->curs + line->pmt_s - 1) % line->col) == 0)
				go_upline(line);
			else
				tputs(tgetstr("le", NULL), 1, ft_intputchar);
		}
		else
			go_left_2(line);
		line->curs--;
	}
}

/********************************************************/

void	go_right_2(t_line *line)
{
	tputs(tgetstr("nd", NULL), 1, ft_intputchar);
	line->curs++;
}

void	go_right_3(t_line *line)
{
	tputs(tgetstr("do", NULL), 1, ft_intputchar);
	line->curs++;
}

void	go_right(t_line *line)
{
	if (line->curs < (int)ft_strlen(line->str))
	{
		if (verify_new_line(line) != 0)
		{
			if (((line->curs + line->pmt_s) % line->col) == 0
			|| line->curs%line->col == 0)
			{
				go_right_2(line);
				return;
			}
			else if ((get_last_newline(line))  % line->col == 0)
			{
				go_right_3(line);
				return;
			}
		}
		if (((line->curs + line->pmt_s) % line->col) == 0)
			tputs(tgetstr("do", NULL), 1, ft_intputchar);
		else if (line->str[line->curs] == '\n')
			tputs(tgetstr("do", NULL), 1, ft_intputchar);
		else
			tputs(tgetstr("nd", NULL), 1, ft_intputchar);
		line->curs++;
	}
}

/********************************************************/

void	go_home(t_line *line)
{
	while (line->curs > 0)
		go_left(line);
}

/********************************************************/

void	go_end(t_line *line)
{
	while (line->curs < (int)ft_strlen(line->str))
		go_right(line);
}
