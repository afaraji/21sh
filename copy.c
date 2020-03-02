/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 22:35:40 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/02 22:35:42 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char	*copy_char_1(t_line *line, int curs)
{
	int		i;
	int		j;
	char	*to_copy;

	to_copy = (char *)malloc(sizeof(char) * (line->curs - curs + 2));
	i = curs;
	j = 0;
	while (i <= line->curs)
	{
		to_copy[j] = line->str[i];
		i++;
		j++;
	}
	to_copy[j] = '\0';
	return (to_copy);
}

char	*copy_char_2(t_line *line, int curs)
{
	int		i;
	int		j;
	char	*to_copy;

	to_copy = (char *)malloc(sizeof(char) * curs + 1);
	i = line->curs;
	j = 0;
	while (i <= curs)
	{
		to_copy[j] = line->str[i];
		i++;
		j++;
	}
	to_copy[j] = '\0';
	return (to_copy);
}

char	*copy_char(t_line *line, int curs)
{
	char	*to_copy;

	if (line->curs > curs)
		to_copy = ft_strdup(copy_char_1(line, curs));
	else
		to_copy = ft_strdup(copy_char_2(line, curs));
	return (to_copy);
}

void	ft_copy(t_line *line, t_select *select, char **to_past)
{
	if (select->on == 1)
	{
		tputs(tgetstr("sc", NULL), 1, ft_intputchar);
		display_line_from_begin(line);
		tputs(tgetstr("rc", NULL), 1, ft_intputchar);
		*to_past = ft_strdup(copy_char(line, select->start));
		select->on = 0;
	}
}
