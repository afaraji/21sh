/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 23:01:41 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/02 23:01:42 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

void	left_select_1(t_line *line)
{
	int i;

	line->curs--;
	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	line->curs++;
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	i = line->curs;
	while (line->str[i])
	{
		ft_putchar(line->str[i]);
		i++;
	}
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
}

void	left_select_2(t_terminal *term)
{
	int i;

	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	i = term->line->curs;
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

void	left_select(t_terminal *term)
{
	if (term->line->curs)
	{
		term->select->len--;
		if (term->select->len >= 0)
			left_select_1(term->line);
		else
			left_select_2(term);
	}
}
