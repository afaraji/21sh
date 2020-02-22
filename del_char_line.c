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
	go_end(line);
	while (line->curs)
		del_char(line);
}
