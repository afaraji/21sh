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

int     is_multline(char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

int		len_str_from_nl(t_line	*line, int pos)
{
	int i;
	int count;

	i = pos;
	count = 0;
	while (i > 0)
	{
		if (line->str[i - 1] == '\n')
			return (count);
		count++;
		i--;
	}
	return (count + line->pmt_s - 1);
	
}

// if line->str[line->curs + 1] == '\n' && len % line->col == 0 (add one line->curs++)

void    go_left(t_line *line)
{
	int len;
	int	tmp;

	if (line->curs > 0)
	{
		if (is_multline(line->str))
		{
			len = len_str_from_nl(line, line->curs);
			if (len == 0)
			{
				tmp = len_str_from_nl(line, line->curs - 1);
				if (tmp == 0)
					tputs(tgetstr("up", NULL), 1, ft_intputchar);
				else
				{
					tmp = tmp % line->col;
					(tmp == 0) ? (tmp = line->col, line->curs--) : 0;
					tputs(tgetstr("up", NULL), 1, ft_intputchar);
					tputs(tgoto(tgetstr("ch", NULL), 0, tmp), 1, ft_intputchar);
				}
			}
			else
			{
				if (len % line->col == 0)
					go_upline(line);
				else
					tputs(tgetstr("le", NULL), 1, ft_intputchar);	
			}
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
