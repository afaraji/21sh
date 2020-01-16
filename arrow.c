
#include "readline.h"


void    go_left(t_line *line)
{
    if(line->curs > 0)
    {
        tputs(tgetstr("le", NULL), 1, ft_intputchar);
        line->curs--;
    }
   
}

void    go_right(t_line *line)
{
    if(line->curs < (int)ft_strlen(line->str))
    {
        tputs(tgetstr("nd", NULL), 1, ft_intputchar);
        line->curs++;
    }
}

void    del_char(t_line *line)
{
    if (line->curs > 0)
    {
        tputs(tgetstr("dc", NULL), 1, ft_intputchar);
        line->curs--;
    }
}