/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_down.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 23:51:06 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/12 23:51:08 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

void	go_down_2(t_line *line)
{
	if (line->str[line->curs] == '\n')
	{
		while (line->curs < (int)ft_strlen(line->str)
		&& line->str[line->curs + 1] != '\n')
			go_right(line);
		go_right(line);
	}
	else
	{
		while (line->curs < (int)ft_strlen(line->str)
		&& line->str[line->curs] != '\n')
			go_right(line);
		while (line->curs < (int)ft_strlen(line->str)
		&& line->str[line->curs + 1] != '\n')
			go_right(line);
		go_right(line);
	}
}

void	go_down_1(t_line *line, char **table)
{
	int	len_2;
	int i;

	i = verify_new_line(line);
	if (table[i + 1])
	{
		if (i == 0)
			len_2 = line->curs + ft_strlen(table[i]) + line->pmt_s;
		else
			len_2 = line->curs + ft_strlen(table[i]) + 1;
		if (len_2 < get_lines_len(table, i + 1))
		{
			while (line->curs < (int)ft_strlen(line->str) && line->curs < len_2)
				go_right(line);
		}
		else
			go_down_2(line);
	}
}

void	go_down(t_line *line)
{
	char	**table;
	int		i;

	table = ft_strsplit_2(line->str, '\n');
	if (line->curs < (int)ft_strlen(line->str))
		go_down_1(line, table);
	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}
