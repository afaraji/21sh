/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_newline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:42:07 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/20 14:42:09 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int	verify_new_line(t_line *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < line->curs)
	{
		if (line->str[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

int	is_multline(char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

int	len_str_from_nl(t_line *line, int pos)
{
	int	i;
	int	count;

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

int	get_lines_len(char **table, int limit)
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
	return (r);
}
