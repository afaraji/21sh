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

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

void	go_right_1(t_line *line)
{
	int len;

	if (line->str[line->curs] == '\n')
	{
		if (line->init_pos != line->row)
			line->init_pos++;
		tputs(tgetstr("do", NULL), 1, ft_intputchar);
	}
	else
	{
		len = len_str_from_nl(line, line->curs) + 1;
		if (line->curs && len % line->col == 0)
		{
			if (line->str[line->curs + 1] == '\n')
				line->curs++;
			if (line->init_pos != line->row)
				line->init_pos++;
			tputs(tgetstr("do", NULL), 1, ft_intputchar);
		}
		else
			tputs(tgetstr("nd", NULL), 1, ft_intputchar);
	}
}

void	go_right(t_line *line)
{
	if (line->curs < (int)ft_strlen(line->str))
	{
		if (is_multline(line->str))
			go_right_1(line);
		else
		{
			if (line->init_pos == line->row
			&& line->curs < ((int)ft_strlen(line->str) - 1)
			&& ((int)ft_strlen(line->str) + line->pmt_s - 2) % line->col == 0)
				tputs(tgetstr("up", NULL), 1, ft_intputchar);
			if ((line->curs + line->pmt_s) % line->col == 0)
			{
				if (line->init_pos != line->row)
					line->init_pos++;
				tputs(tgetstr("do", NULL), 1, ft_intputchar);
			}
			else
				tputs(tgetstr("nd", NULL), 1, ft_intputchar);
		}
		line->curs++;
	}
}
