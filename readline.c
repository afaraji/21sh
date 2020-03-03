/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 19:33:46 by sazouaka          #+#    #+#             */
/*   Updated: 2020/01/18 19:33:48 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_line	*init_line(char *prompt)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	line->curs = 0;
	line->str = ft_strdup("");
	line->pmt_s = ft_strlen(prompt) + 1;
	line->col = tgetnum("co");
	return (line);
}

void	ft_prompt(char *prompt)
{
	ft_putstr("\x1B[35m");
	ft_putstr(prompt);
	ft_putstr("\x1b[39m");
}

void	get_cmd(t_line *line, char buff, t_hist **his_head)
{
	line->str = join_line(line->str, buff, line->curs);
	display_line(line);
	go_right(line);
	if (buff == ENTER)
	{
		line->str = trim_cmd(line->str);
		if (ft_strcmp(line->str, "") != 0)
			add_cmd_to_his_list(line->str, his_head);
	}
}

int		printable(t_line *line, t_hist **his_head, t_select *select, int buff)
{
	int	curs;

	if ((ft_isprint(buff) || buff == ENTER))
	{
		if (select->on == 1)
		{
			select->on = 0;
			tputs(tgetstr("sc", NULL), 1, ft_intputchar);
			display_line_from_begin(line);
			tputs(tgetstr("rc", NULL), 1, ft_intputchar);
		}
		else
		{
			get_cmd(line, buff, his_head);
			if (buff == ENTER)
			{
				curs = line->curs;
				while (curs <= (int)ft_strlen(line->str))
				{
					go_right(line);
					curs++;
				}
				return (1);
			}
		}
	}
	return (0);
}

int		unprintable_2(t_line *line, t_select *select, int buff)
{
	if (buff == LFTARROW)
	{
		if (select->on)
			left_select(line, select);
		go_left(line);
		return (1);
	}
	else if (buff == RTARROW)
	{
		if (select->on)
			right_select(line, select);
		go_right(line);
		return (1);
	}
	return (0);
}

int		unprintable(t_line *line, t_select *select, int buff, char **to_past)
{
	if (buff == SELECT)
	{
		select->len = 0;
		select->on = 1;
		select->start = line->curs;
		return (1);
	}
	else if (buff == COPY)
	{
		ft_copy(line, select, to_past);
		return (1);
	}
	else if (buff == CUT)
	{
		ft_cut(line, select, to_past);
		return (1);
	}
	else if (buff == PAST && *to_past)
	{
		past(line, to_past);
		return (1);
	}
	else if (unprintable_2(line, select, buff))
		return (1);
	return (0);
}

char	*read_line(char *prompt, t_hist **his_head)
{
	int			buff;
	t_line		*line;
	int			index;
	t_select	*select;
	static char	*to_past = NULL;

	buff = 0;
	index = 0;
	select = (t_select *)malloc(sizeof(t_select));
	select->on = 0;
	line = init_line(prompt);
	if (read(0, &buff, 0) < 0)
		return (NULL);
	ft_prompt(prompt);
	while (1)
	{
		buff = 0;
		read(0, &buff, 4);
		if (printable(line, his_head, select, buff))
			break ;
		else if (!(ft_isprint(buff)))
		{
			if (unprintable(line, select, buff, &to_past))
				continue;
			else
			{
				move_curs(line, buff, select);
				navigate_history(line, buff, his_head, &index);
				move_by_word(line, buff);
			}
		}
	}
	return (line->str);
}

// char	*readline(int prompt)
// {
// 	char *prmt;

// 	if (prompt == 0)
// 		prmt = "$> ";
// 	else if (prompt == 1)
// 		prmt = "quote> ";
// 	else if (prompt == 2)
// 		prmt = "dquote> ";
// 	else if (prompt == 3)
// 		prmt = "heredoc> ";
// 	else if (prompt == 4)
// 		prmt = "pipe> ";
// }

