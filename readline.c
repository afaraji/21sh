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
#include "parse.h"

void	ft_prompt(char *prompt)
{
	ft_putstr("\x1B[35m");
	ft_putstr(prompt);
	ft_putstr("\x1b[39m");
}

int get_current_row(void)
{
	char buf[30];
	int row = 0;
	int ch = 0;
	int i = 0;
	write(1, "\033[6n", 4);
	while(ch !='R')
	{
		read(0, &ch, 1);
		buf[i] = ch;
		i++;
	}
	if((buf[3]) >= '0' && (buf[3] <= '9'))
		row = ((buf[2] - '0') * 10 ) + (buf[3] - '0');
	else
		row =  buf[2] - '0';
	return(row);
}

t_line	*init_line(char *prompt)
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
	if (!(term->select = (t_select *)malloc(sizeof(t_select))))
		return (NULL);
	term->select->on = 0;
	return (term);
}

char		*manage_line(char *prompt, t_hist **his_head, int mult_line)
{
	t_terminal	*term;
	static char	*to_past = NULL;
	char		*tmp;
	int			unprint_ret;

	term = initiate_unprint_var();
	term->line = init_line(prompt);
	if (read(0, &term->buff, 0) < 0)
		return (NULL);
	ft_prompt(prompt);
	while (1)
	{
		term->buff = 0;
		read(0, &term->buff, 4);
		//******** neeed to be in a func *********
		if (term->buff == CTRL_C)
		{
			ft_putstr_fd("^C\n", 1);
			if (mult_line != 0)
				return(ft_strdup("\033"));
			return (ft_strdup(""));
			
		}
		if (term->buff == CTRL_D && !ft_strcmp(term->line->str, ""))
		{
			if (mult_line == 0)
				ft_exit(-1);
			return(ft_strdup("\030"));
		}
		if (term->buff == CTRL_L && mult_line == 0)
		{
			ft_putstr_fd("\033[H\033[2J", 1);
			ft_prompt("$> ");
			ft_putstr(term->line->str);
			// return (ft_strdup(""));
		}
		//**********************************************
		if (printable(term, his_head, mult_line))
			break ;
		else if (!(ft_isprint(term->buff)))
		{
			unprint_ret = unprintable(term, his_head, &to_past);
			if (unprint_ret == 1)
				continue;
			else if (unprint_ret == 2)
			{
				ft_prompt("\n$> ");
				ft_putstr(term->line->str);
			}
		}
	}
	tmp = ft_strdup(term->line->str);
	free_term(&term);
	return (tmp);
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
