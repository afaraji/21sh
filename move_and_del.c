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
    if(line->curs > 0)
    {
        tputs(tgetstr("le", NULL), 1, ft_intputchar);
        line->curs--;
    }
}
/********************************************************/
void    go_right(t_line *line)
{
    if (line->curs < (int)ft_strlen(line->str))
    {
        if (line->str[line->curs] == '\n')
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
