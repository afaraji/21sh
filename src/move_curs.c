/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_curs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 22:30:54 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/12 22:30:56 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

void	move_curs(t_terminal *term)
{
	if (term->select->on == 1)
	{
		term->select->on = 0;
		tputs(tgetstr("sc", NULL), 1, ft_intputchar);
		display_line_from_begin(term->line);
		tputs(tgetstr("rc", NULL), 1, ft_intputchar);
	}
	if (term->buff == DEL)
		del_char(term->line);
	else if (term->buff == HOME)
		go_home(term->line);
	else if (term->buff == END)
		go_end(term->line);
	else if (term->buff == UPLINE)
		go_up(term->line);
	else if (term->buff == DWNLINE)
		go_down(term->line);
}
