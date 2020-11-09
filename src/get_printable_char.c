/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_printable_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:03:32 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/04 00:03:34 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int		get_cmd_1(char **str1, char **str2)
{
	if (*str1)
	{
		ft_strdel(str2);
		*str2 = ft_strdup(*str1);
		ft_putstr_fd("\n", STDOUT);
		ft_putstr_fd(*str2, STDOUT);
		ft_strdel(str1);
		return (0);
	}
	ft_putstr_fd("\n21sh: ", STDERR);
	ft_putstr_fd(*str2, STDERR);
	ft_putstr_fd(": event not found", STDERR);
	ft_strdel(str2);
	ft_strdel(str1);
	*str2 = ft_strdup("");
	return (1);
}

int		get_cmd(t_terminal *term, t_hist **his_head, int mult_line)
{
	char	*tmp;

	term->line->str = join_line(term->line->str, term->buff, term->line->curs);
	display_line(term->line);
	go_right(term->line);
	if (term->buff == ENTER)
	{
		if (term->line->str[0] == '!' && term->line->str[1])
		{
			tmp = history_search(term->line->str + 1, his_head);
			if (get_cmd_1(&tmp, &(term->line->str)) == 1)
				return (1);
		}
		if (ft_strcmp(term->line->str, "") != 0
		|| (mult_line != 0 && mult_line != -1))
			add_cmd_to_his_list(term->line->str, his_head, mult_line);
	}
	return (0);
}

void	printable_1(t_terminal *term)
{
	term->select->on = 0;
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	display_line_from_begin(term->line);
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
}

int		printable(t_terminal *term, t_hist **his_head, int mult_line)
{
	int	curs;

	if ((ft_isprint(term->buff) || term->buff == ENTER))
	{
		term->tab_on = 0;
		if (term->select->on == 1)
			printable_1(term);
		else
		{
			get_cmd(term, his_head, mult_line);
			if (term->buff == ENTER)
			{
				curs = term->line->curs;
				while (curs <= (int)ft_strlen(term->line->str))
				{
					go_right(term->line);
					curs++;
				}
				ft_putchar('\n');
				return (1);
			}
		}
	}
	return (0);
}
