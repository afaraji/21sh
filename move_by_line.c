/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_by_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 23:51:06 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/12 23:51:08 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		get_lines_len(char **table, int limit)
{
	int r;
	int i;

	r = 0;
	i = 0;
	while (i <= limit)
	{
		r = r + 1 + ft_strlen(table[i]);
		i++;
	}
	return(r);
}

void	go_up_2(t_line *line, char **table)
{
	int	len_2;
	int i;


	i = verify_new_line(line);
	if ((i - 1) >= 0)
	{
		if (i == 1)
			len_2 = line->curs - line->pmt_s - ft_strlen(table[i - 1]);
		else
			len_2 = line->curs - ft_strlen(table[i - 1]) - 1;
		if (len_2 >= get_lines_len(table, i - 1))
		{
			if (line->str[line->curs] == '\n')
				line->curs--;
			while (line->curs > 0 && line->str[line->curs] != '\n')
				go_left(line);
		}
		else
		{
			while (line->curs > 0 && line->curs > len_2)
				go_left(line);
		}
	}
}

void	go_up(t_line *line)
{
	char	**table;

	table = ft_strsplit_2(line->str, '\n');
	if (line->curs > 0)
	{
		go_up_2(line, table);
	}
}

void	go_down_2(t_line *line, char **table)
{
	(void)table;
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
			fprintf(ttyfd, "*** 1 \n");
			while (line->curs < (int)ft_strlen(line->str) && line->curs < len_2)
				go_right(line);
		}
		else
		{
			fprintf(ttyfd, "*** 2 \n");
			if (line->str[line->curs] == '\n')
			{
				while (line->curs < (int)ft_strlen(line->str) && line->str[line->curs + 1] != '\n')
					go_right(line);
				go_right(line);
			}
			else
			{
				while (line->curs < (int)ft_strlen(line->str) && line->str[line->curs] != '\n')
					go_right(line);
				while (line->curs < (int)ft_strlen(line->str) && line->str[line->curs + 1] != '\n')
					go_right(line);
				go_right(line);
			}
		}
	}
}

void	go_down(t_line *line)
{
	char	**table;

	table = ft_strsplit_2(line->str, '\n');
	if (line->curs < (int)ft_strlen(line->str))
		go_down_2(line, table);
}
