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


void    go_left(t_line *line)
{
    int i;

    i = 0;
    if(line->curs > 0)
    {
        tputs(tgetstr("le", NULL), 1, ft_intputchar);
        line->curs--;
        if (((line->curs + line->pmt_s) % line->col) == 0)
        {
            tputs(tgetstr("up", NULL), 1, ft_intputchar);
            while (i < line->col)
            {
                tputs(tgetstr("nd", NULL), 1, ft_intputchar);
                i++;
            }
        }
    }
}		

/********************************************************/
void    go_right(t_line *line)
{
    if (line->curs < (int)ft_strlen(line->str))
    {
        if (line->str[line->curs] == '\n' || ((line->curs + line->pmt_s) % line->col) == 0)
            tputs(tgetstr("do", NULL), 1, ft_intputchar);
        else
            tputs(tgetstr("nd", NULL), 1, ft_intputchar);
        line->curs++;
    }
}
/********************************************************/
void    go_home(t_line *line)
{
    while (line->curs > 0)
        go_left(line);
}
/********************************************************/
void    go_end(t_line *line)
{
    while (line->curs <  (int)ft_strlen(line->str))
        go_right(line);
}
/********************************************************/
void    del_char(t_line *line)
{
    if (line->curs > 0)
    {
        go_left(line);
        line->str = trim_pos(line->str, line->curs);
        display_line(line);
    }
}
/********************************************************/
void    del_line(t_line *line)
{
    int i;

    i = ft_strlen(line->str);
    while (line->curs < i)
        go_right(line);
    while (i > 0)
    {
        go_left(line);
        tputs(tgetstr("dc", NULL), 1, ft_intputchar);
        i--;
    }
}