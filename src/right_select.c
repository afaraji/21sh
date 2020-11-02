/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_select.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 23:06:05 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/02 23:06:07 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

void	right_select_1(t_line *line)
{
	int i;

	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	ft_putstr("\e[45m");
	ft_putchar(line->str[line->curs]);
	ft_putstr("\e[0m");
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
	go_right(line);
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	i = line->curs;
	while (line->str[i])
	{
		ft_putchar(line->str[i]);
		i++;
	}
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
	go_left(line);
}

void	right_select_2(t_terminal *term)
{
	int i;

	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	ft_putchar(term->line->str[term->line->curs]);
	i = term->line->curs + 1;
	ft_putstr("\e[45m");
	while (term->line->str[i] != '\0' && i <= term->select->start)
	{
		ft_putchar(term->line->str[i]);
		i++;
	}
	ft_putstr("\e[0m");
	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	while (term->line->str[i])
	{
		ft_putchar(term->line->str[i]);
		i++;
	}
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
}

void	right_select(t_terminal *term)
{
	if (term->line->str[term->line->curs])
	{
		if (term->select->len >= 0)
			right_select_1(term->line);
		else
			right_select_2(term);
		term->select->len++;
	}
}
