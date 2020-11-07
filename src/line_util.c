/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 22:32:28 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/12 22:32:31 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int		ft_intputchar(int c)
{
	char ch;

	ch = c;
	return (write(1, &ch, 1));
}

void	display_line(t_line *line)
{
	int	i;

	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	i = line->curs;
	while (i < (int)ft_strlen(line->str))
	{
		ft_putchar(line->str[i]);
		i++;
	}
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
}

void	display_line_from_begin(t_line *line)
{
	int	i;
	int curs;

	curs = line->curs;
	go_home(line);
	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	i = line->curs;
	while (i < (int)ft_strlen(line->str))
	{
		ft_putchar(line->str[i]);
		i++;
	}
	while (curs)
	{
		line->curs++;
		curs--;
	}
}

void	del_char(t_line *line)
{
	char	*tmp;

	if (line->curs > 0)
	{
		go_left(line);
		tmp = line->str;
		line->str = trim_pos(line->str, line->curs);
		ft_strdel(&tmp);
		display_line(line);
	}
}

void	del_line(t_line *line)
{
	go_end(line);
	while (line->curs)
		del_char(line);
}
