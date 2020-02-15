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

void	go_up(t_line *line,int curs)
{
	int i;

	i = verify_new_line(line);
	fprintf(ttyfd, "%d\n", get_last_newline(line));
	fprintf(ttyfd, "line->col %d\n", line->col);
	while (line->curs && line->curs >= (curs - line->col) + 1)
	{
		//fprintf(ttyfd, "curs : %d , line->curs : %d, line->col : %d\n",curs, line->curs,  line->col);
		go_left(line);
	}
	if (i != verify_new_line(line))
	{

		int j = (line->curs - line->col);
		while (line->curs > j)
		{
			//fprintf(ttyfd, "line->curs : %d, line->col : %d, (line->curs - line->col) : %d\n", line->curs, line->col ,  (line->curs - line->col));
			go_left(line);
		}
	}
}

void	go_down(t_line *line,int curs)
{
	int len;
	
	len = ft_strlen(line->str);
	while (line->curs < len && line->curs <= (curs + line->col) - 1)
	{
		//fprintf(ttyfd, "line->curs : %d, line->col : %d", line->curs,  line->col);
		go_right(line);
	}
}
