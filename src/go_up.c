/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_up.c                                            :+:      :+:    :+:   */
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

void	go_up_1(t_line *line, char **table)
{
	int	len;
	int i;

	i = verify_new_line(line);
	if ((i - 1) >= 0)
	{
		if (i == 1)
			len = line->curs - line->pmt_s - ft_strlen(table[i - 1]);
		else
			len = line->curs - ft_strlen(table[i - 1]) - 1;
		if (len >= get_lines_len(table, i - 1))
		{
			if (line->str[line->curs] == '\n')
				line->curs--;
			while (line->curs > 0 && line->str[line->curs] != '\n')
				go_left(line);
		}
		else
		{
			while (line->curs > 0 && line->curs > len)
				go_left(line);
		}
	}
}

void	go_up(t_line *line)
{
	char	**table;
	int		i;

	table = ft_strsplit_2(line->str, '\n');
	if (line->curs > 0)
		go_up_1(line, table);
	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}
