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

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

void		ft_prompt(char *prompt)
{
	ft_putstr("\x1B[35m");
	ft_putstr(prompt);
	ft_putstr("\x1b[39m");
}

int			get_current_row(void)
{
	char	buf[30];
	int		row;
	int		ch;
	int		i;

	row = 0;
	ch = 0;
	i = 0;
	write(1, "\033[6n", 4);
	while (ch != 'R')
	{
		read(0, &ch, 1);
		buf[i] = ch;
		i++;
	}
	if ((buf[3]) >= '0' && (buf[3] <= '9'))
		row = ((buf[2] - '0') * 10) + (buf[3] - '0');
	else
		row = buf[2] - '0';
	return (row);
}

t_line		*init_line(char *prompt)
{
	t_line	*line;

	if (!(line = (t_line *)malloc(sizeof(t_line))))
		return (NULL);
	line->init_pos = get_current_row();
	line->curs = 0;
	line->str = ft_strdup("");
	line->pmt_s = ft_strlen(prompt) + 1;
	line->col = tgetnum("co");
	line->row = tgetnum("li");
	return (line);
}

t_terminal	*initiate_unprint_var(void)
{
	t_terminal	*term;

	if (!(term = (t_terminal *)malloc(sizeof(t_terminal))))
		return (NULL);
	term->index = 0;
	term->tab_on = 0;
	if (!(term->select = (t_select *)malloc(sizeof(t_select))))
		return (NULL);
	term->select->on = 0;
	return (term);
}

char		*readline(int prompt)
{
	char *prmt;

	if (prompt == 0)
		prmt = "$> ";
	else if (prompt == -1)
		prmt = "$> ";
	else if (prompt == QUOTE)
		prmt = "quote> ";
	else if (prompt == DQUOTE)
		prmt = "dquote> ";
	else if (prompt == SMLSML)
		prmt = "heredoc> ";
	else if (prompt == PIP)
		prmt = "pipe> ";
	else
		prmt = "> ";
	return (manage_line(prmt, &(g_var.history), prompt));
}
