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


#include "readline.h"

int		verify_new_line(t_line *line)
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
	return (count);
}

int		left_newline(t_line *line)
{
	int j;
	int count;
	j = 0;
	count = 0;
	while (j < (*line).curs)
	{
		count++;
		if ((*line).str[j] == '\n')
			count = 0;
		j++;
	}
	if ((count % (*line).col) == 0)
    {
		return (1);
    }
	return (0);
}



int		len_between_newlines(t_line *line)
{
	int i;
	int count;

	i = 0;
	while (i < line->curs)
	{
		if (line->str[i] == '\n')
			count = 0;
		i++;
		count++;
	}
	return (count);
}