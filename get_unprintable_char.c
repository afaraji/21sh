/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_unprintable_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:05:21 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/04 00:05:22 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		unprintable_2(t_line *line, t_select *select, int buff)
{
	if (buff == LFTARROW)
	{
		if (select->on)
			left_select(line, select);
		go_left(line);
		return (1);
	}
	else if (buff == RTARROW)
	{
		if (select->on)
			right_select(line, select);
		go_right(line);
		return (1);
	}
	return (0);
}

int		unprintable(t_line *line, t_select *select, int buff, char **to_past)
{
	if (buff == SELECT)
	{
		select->len = 0;
		select->on = 1;
		select->start = line->curs;
		return (1);
	}
	else if (buff == COPY)
	{
		ft_copy(line, select, to_past);
		return (1);
	}
	else if (buff == CUT)
	{
		ft_cut(line, select, to_past);
		return (1);
	}
	else if (buff == PAST && *to_past)
	{
		past(line, to_past);
		return (1);
	}
	else if (unprintable_2(line, select, buff))
		return (1);
	return (0);
}