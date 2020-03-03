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

t_select	*initiate_variables(int *buff, int *index)
{
	t_select	*select;

	*buff = 0;
	*index = 0;
	select = (t_select *)malloc(sizeof(t_select));
	select->on = 0;
	return (select);
}

char	*manage_line(char *prompt, t_hist **his_head)
{
	int			buff;
	t_line		*line;
	int			index;
	t_select	*select;
	static char	*to_past = NULL;

	select = initiate_variables(&buff, &index);
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

char	*readline(int prompt, t_hist **his_list)
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

