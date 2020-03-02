/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   past.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 23:05:08 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/02 23:05:09 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

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
