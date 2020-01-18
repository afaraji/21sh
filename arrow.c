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
    if(line->curs < (int)ft_strlen(line->str))
    {
        tputs(tgetstr("nd", NULL), 1, ft_intputchar);
        line->curs++;
    }
}
/********************************************************/
void    del_char(t_line *line)
{
    if (line->curs > 0)
    {
        /***************************/
        /***** fixe this part ******/
        /***************************/
        tputs(tgetstr("le", NULL), 1, ft_intputchar);
        tputs(tgetstr("dc", NULL), 1, ft_intputchar);
        line->str = ft_strsub(line->str, 0, ft_strlen(line->str) - 1);
        line->curs--;
    }
}
/********************************************************/
void    go_home(t_line *line)
{
    int i;

    i = line->curs;
    while (i > 0)
    {
        tputs(tgetstr("le", NULL), 1, ft_intputchar);
        i--;
    }
    line->curs = 0;
}
/********************************************************/
void    go_end(t_line *line)
{
    int i;

    if (line->curs != (int)ft_strlen(line->str))
    {
        i = (int)ft_strlen(line->str) - line->curs;
        while (i > 0)
        {
            
            tputs(tgetstr("nd", NULL), 1, ft_intputchar);
            i--;
        }
    }
    line->curs = (int)ft_strlen(line->str);
}
/********************************************************/
void    go_down(t_line *line)
{
    /**********************************/
    /****** verify if is correct ******/
    /**********************************/
    tputs(tgetstr("do", NULL), 1, ft_intputchar);
    line->str = ft_strdup("");
    line->curs = 0;
}
