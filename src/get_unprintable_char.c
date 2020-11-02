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

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int		tabulation_on(t_terminal *term)
{
	if (term->buff == TAB)
	{
		term->tab_on = 1;
		return (auto_completion(term->line));
	}
	return (0);
}

int		unprintable_2(t_terminal *term)
{
	if (term->buff == LFTARROW)
	{
		if (term->select->on)
			left_select(term);
		go_left(term->line);
		return (1);
	}
	else if (term->buff == RTARROW)
	{
		if (term->select->on)
			right_select(term);
		go_right(term->line);
		return (1);
	}
	return (0);
}

int		unprintable_1(t_terminal *term, char **to_past)
{
	if (term->buff == SELECT)
	{
		term->select->len = 0;
		term->select->on = 1;
		term->select->start = term->line->curs;
		return (1);
	}
	else if (term->buff == COPY)
	{
		ft_copy(term, to_past);
		return (1);
	}
	else if (term->buff == CUT)
	{
		ft_cut(term, to_past);
		return (1);
	}
	else if (term->buff == PAST && *to_past)
	{
		past(term->line, to_past);
		return (1);
	}
	else if (unprintable_2(term))
		return (1);
	return (0);
}

int		unprintable(t_terminal *term, t_hist **his_head, char **to_past)
{
	int tab_ret;

	tab_ret = tabulation_on(term);
	if (tab_ret == 1)
		return (1);
	else if (tab_ret == 2)
		return (2);
	else if (term->tab_on == 0 && unprintable_1(term, to_past))
		return (3);
	else
	{
		move_curs(term);
		navigate_history(term, his_head);
		move_by_word(term->line, term->buff);
		return (4);
	}
	return (0);
}
