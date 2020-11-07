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

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

void	ft_cut_1(t_terminal *term, int curs, char *tmp_s)
{
	char	*tmp1;
	char	*tmp2;

	if (curs >= term->select->start)
	{
		tmp1 = ft_strsub(tmp_s, 0, term->select->start);
		tmp2 = ft_strsub(tmp_s, curs + 1, ft_strlen(tmp_s));
	}
	else
	{
		tmp1 = ft_strsub(tmp_s, 0, curs);
		tmp2 = ft_strsub(tmp_s, term->select->start + 1, ft_strlen(tmp_s));
	}
	ft_strdel(&(term->line->str));
	term->line->str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
}

void	ft_cut(t_terminal *term, char **to_past)
{
	char	*tmp_s;
	int		curs;

	if (term->select->on == 1)
	{
		if (*to_past)
			ft_strdel(to_past);
		*to_past = copy_char(term->line, term->select->start);
		tmp_s = ft_strdup(term->line->str);
		curs = term->line->curs;
		go_home(term->line);
		tputs(tgetstr("cd", NULL), 1, ft_intputchar);
		ft_cut_1(term, curs, tmp_s);
		ft_strdel(&tmp_s);
		while (term->line->str[term->line->curs] != '\0'
		&& term->line->str[term->line->curs])
		{
			ft_putchar(term->line->str[term->line->curs]);
			term->line->curs++;
		}
		while (term->line->curs && term->line->curs > curs)
			go_left(term->line);
		term->select->on = 0;
	}
}
