/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:11:59 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/27 16:12:01 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	right_select_1(t_line *line)
{
    int i;

    tputs(tgetstr("cd", NULL), 1, ft_intputchar);
    tputs(tgetstr("sc", NULL), 1, ft_intputchar);
    ft_putstr("\e[45m");
    ft_putchar(line->str[line->curs]);
    ft_putstr("\e[0m");
    tputs(tgetstr("rc", NULL), 1, ft_intputchar);
    go_right(line);
    tputs(tgetstr("sc", NULL), 1, ft_intputchar);
    i = line->curs;
    while (line->str[i])
    {
        ft_putchar(line->str[i]);
        i++;
    }
    tputs(tgetstr("rc", NULL), 1, ft_intputchar);
    go_left(line);
}

void	right_select_2(t_line *line, t_select *select)
{
    int i;

    tputs(tgetstr("cd", NULL), 1, ft_intputchar);
    tputs(tgetstr("sc", NULL), 1, ft_intputchar);
    ft_putchar(line->str[line->curs]);
    i = line->curs + 1;
    ft_putstr("\e[45m");
    while (i <= select->start)
    {
        ft_putchar(line->str[i]);
        i++;
    }
    ft_putstr("\e[0m");
    tputs(tgetstr("cd", NULL), 1, ft_intputchar);
    while (line->str[i])
    {
        ft_putchar(line->str[i]);
        i++;
    }
    tputs(tgetstr("rc", NULL), 1, ft_intputchar);
}

void	right_select(t_line *line, t_select *select)
{
	if (line->str[line->curs])
	{
		if (select->len >= 0)
            right_select_1(line);
		else
			right_select_2(line, select);
		select->len++;
	}
}
