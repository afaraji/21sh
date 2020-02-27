/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_past.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 17:04:52 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/23 17:04:53 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char	*copy_char(t_line *line, int curs)
{
	int		i;
	int		j;
	char	*to_copy;

	
	j = 0;
	if (line->curs > curs)
	{
		to_copy = (char *)malloc(sizeof(char) * (line->curs - curs + 2));
		i = curs;
		while (i <= line->curs)
		{
			to_copy[j] = line->str[i];
			i++;
			j++;
		}
	}
	else
	{
		to_copy = (char *)malloc(sizeof(char) * curs + 1);
		i = line->curs;
		while (i <= curs)
		{
			to_copy[j] = line->str[i];
			i++;
			j++;
		}
	}
	to_copy[j] = '\0';
	return (to_copy);
}

void	past_char(t_line *line)
{
	int	i;

	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	i = 0;
	while (i < (int)ft_strlen(line->str))
	{
		ft_putchar(line->str[i]);
		i++;
	}
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
}

char	*join_lines_to_past(t_line *line, char *to_past)
{
	int		curs;
	char	*tmp1;
	char	*tmp2;
	char	*str;

	curs = line->curs;
	tmp1 = ft_strsub(line->str, 0, curs);
	tmp2 = ft_strjoin(tmp1, to_past);
	str = ft_strjoin(tmp2, &line->str[curs]);
	return (str);
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

void	past(t_line *line, char **to_past)
{
	int i;

	i = line->curs + (int)ft_strlen(*to_past);
	line->str = join_lines_to_past(line, *to_past);
	while (line->curs > 0)
		go_left(line);
	past_char(line);
	while (line->curs < i)
		go_right(line);
}
