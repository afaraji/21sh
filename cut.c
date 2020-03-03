/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 22:49:47 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/02 22:49:49 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	ft_cut_2(t_line *line, t_select *select, int curs, char *tmp_s)
{
	char	*tmp1;
	char	*tmp2;

	if (curs >= select->start)
	{
		tmp1 = ft_strsub(tmp_s, 0, select->start);
		tmp2 = ft_strsub(tmp_s, curs + 1, ft_strlen(tmp_s));
	}
	else
	{
		tmp1 = ft_strsub(tmp_s, 0, curs);
		tmp2 = ft_strsub(tmp_s, select->start + 1, ft_strlen(tmp_s));
	}
	ft_strdel(&line->str);
	line->str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
}

void	ft_cut(t_line *line, t_select *select, char **to_past)
{
	char	*tmp_s;
	int		curs;

	if (select->on == 1)
	{
		*to_past = ft_strdup(copy_char(line, select->start));
		tmp_s = ft_strdup(line->str);
		curs = line->curs;
		go_home(line);
		tputs(tgetstr("cd", NULL), 1, ft_intputchar);
		ft_cut_2(line, select, curs, tmp_s);
		free(tmp_s);
		while (line->str[line->curs])
		{
			ft_putchar(line->str[line->curs]);
			line->curs++;
		}
		while (line->curs && line->curs >= curs)
			go_left(line);
		select->on = 0;
	}
}
