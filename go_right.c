/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_right.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:40:42 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/20 14:40:44 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		verify_nl(t_line *line)
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
	return(count);
}

void	go_right_3(t_line *line)
{
	tputs(tgetstr("do", NULL), 1, ft_intputchar);
	line->curs++;
}

void	go_right_2(t_line *line)
{
	tputs(tgetstr("nd", NULL), 1, ft_intputchar);
	line->curs++;
}

void	go_right(t_line *line)
{
	int len;

	if (line->curs < (int)ft_strlen(line->str))
	{
		if (is_multline(line->str))
		{
			if (line->str[line->curs] == '\n')
			{
				tputs(tgetstr("do", NULL), 1, ft_intputchar);
			}
			else
			{
				len = len_str_from_nl(line, line->curs) + 1;
				if (line->curs && len % line->col == 0)
				{
					if (line->str[line->curs + 1] == '\n')
						line->curs++;
					tputs(tgetstr("do", NULL), 1, ft_intputchar);
				}
				else
				{
					tputs(tgetstr("nd", NULL), 1, ft_intputchar);
				}
			}
			
			
		}
		else
		{
			if ((line->curs + line->pmt_s) % line->col == 0)
			{
				tputs(tgetstr("do", NULL), 1, ft_intputchar);
			}
			else
			{
				tputs(tgetstr("nd", NULL), 1, ft_intputchar);
			}
		}
		line->curs++;
	}
}


// void	go_right(t_line *line)
// {
// 	if (line->curs < (int)ft_strlen(line->str))
// 	{
// 		if (verify_new_line(line) != 0)
// 		{
// 			if (((line->curs + line->pmt_s) % line->col) == 0
// 			|| line->curs%line->col == 0)
// 			{
// 				go_right_2(line);
// 				return;
// 			}
// 			else if ((len_between_newlines(line))  % line->col == 0)
// 			{
// 				go_right_3(line);
// 				return;
// 			}
// 		}
// 		if (((line->curs + line->pmt_s) % line->col) == 0)
// 			tputs(tgetstr("do", NULL), 1, ft_intputchar);
// 		else if (line->str[line->curs] == '\n')
// 		{
// 			fprintf(ttyfd, "got here\n");
// 			tputs(tgetstr("do", NULL), 1, ft_intputchar);
// 		}
// 		else
// 			tputs(tgetstr("nd", NULL), 1, ft_intputchar);
// 		line->curs++;
// 	}
// }