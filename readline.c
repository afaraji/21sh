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

t_terminal	*initiate_unprint_var(void)
{
	t_terminal	*term;

	term = (t_terminal *)malloc(sizeof(t_terminal));
	term->index = 0;
	term->select = (t_select *)malloc(sizeof(t_select));
	term->select->on = 0;
	return (term);
}

char		*manage_line(char *prompt, t_hist **his_head)
{
	t_terminal	*term;
	static char	*to_past = NULL;

	term = initiate_unprint_var();
	term->line = init_line(prompt);
	if (read(0, &term->buff, 0) < 0)
		return (NULL);
	ft_prompt(prompt);
	while (1)
	{
		term->buff = 0;
		read(0, &term->buff, 4);
		if (printable(term, his_head))
			break ;
		else if (!(ft_isprint(term->buff)))
			unprintable(term, his_head, &to_past);
	}
	return (term->line->str);
}

char		*readline(int prompt, t_hist **his_list)
{
	char *prmt;

	if (prompt == 0)
		prmt = "$> ";
	else if (prompt == -1)
		prmt = "$> ";
	else if (prompt == 1)
		prmt = "quote> ";
	else if (prompt == 2)
		prmt = "dquote> ";
	else if (prompt == 3)
		prmt = "heredoc> ";
	else if (prompt == 4)
		prmt = "pipe> ";
	else
		prmt = "> ";
	return (manage_line(prmt, his_list));
}
