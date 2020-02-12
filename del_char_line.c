/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_char_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 23:08:18 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/12 23:08:20 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	del_char(t_line *line)
{
	if (line->curs > 0)
	{
		go_left(line);
		line->str = trim_pos(line->str, line->curs);
		display_line(line);
	}
}

void	del_line(t_line *line)
{
	int i;

	i = ft_strlen(line->str);
	while (line->curs < i)
		go_right(line);
	while (i > 0)
	{
		go_left(line);
		tputs(tgetstr("dc", NULL), 1, ft_intputchar);
		i--;
	}
}
