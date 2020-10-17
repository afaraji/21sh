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

t_line	*init_line(char *prompt)
{
	t_line	*line;

	if (!(line = (t_line *)malloc(sizeof(t_line))))
		return (NULL);
	line->curs = 0;
	line->str = ft_strdup("");
	line->pmt_s = ft_strlen(prompt) + 1;
	line->col = tgetnum("co");
	line->nline = tgetnum("li");
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

	term = initiate_unprint_var();
	term->line = init_line(prompt);
	if (read(0, &term->buff, 0) < 0)
		return (NULL);
	ft_prompt(prompt);
	while (1)
	{
		term->buff = 0;
		read(0, &term->buff, 4);
		if (ft_strcmp(prompt, "---PRESS TAB FOR MORE---") && printable(term, his_head, mult_line))
			break ;
		else if (!(ft_isprint(term->buff)))
			unprintable(term, his_head, &to_past, prompt);
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
	else if (prompt == COMPL)
		prmt = "---PRESS TAB FOR MORE---";
	else if (prompt == QUOTE)
		prmt = "\nquote> ";
	else if (prompt == DQUOTE)
		prmt = "\ndquote> ";
	else if (prompt == SMLSML)
		prmt = "\nheredoc> ";
	else if (prompt == PIP)
		prmt = "\npipe> ";
	else
		prmt = "\n> ";
	return (manage_line(prmt, &(g_var.history), prompt));
}
