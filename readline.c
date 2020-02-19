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

/*****************************************************************/
/****** - manage multiple spaces on moving left and right by word *******/
/****** - reinicialiser termcap avant exit *****/
/****** - find a solution for copy past with mouse *******/
/****************************************************************/

t_line	*init_line(char *prompt)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	line->curs = 0;
//	line->cmd = ft_strdup("");
	line->str = ft_strdup("");
	line->pmt_s = ft_strlen(prompt);
	line->col = tgetnum("co");
	return (line);
}

/****************************************************************/

void	ft_prompt(char *prompt)
{
	ft_putstr("\x1B[35m");
	ft_putstr(prompt);
	ft_putstr("\x1b[39m");
}

/****************************************************************/

void	get_cmd(t_line *line, char buff, t_hist **his_head)
{
	line->str = join_line(line->str, buff, line->curs);
	display_line(line);
	go_right(line);
	if (buff == ENTER)
	{
		// line->cmd = trim_cmd(ft_strjoin(line->cmd, line->str));
		// if (ft_strcmp(line->cmd, "") != 0)
		// 	add_cmd_to_his_list(line->cmd, his_head);
		line->str = trim_cmd(line->str);
		if (ft_strcmp(line->str, "") != 0)
			add_cmd_to_his_list(line->str, his_head);
	}
}

/****************************************************************/

char	*read_line(char *prompt, t_hist **his_head)
{
	int		buff;
	t_line	*line;
	int		curs;
	int		index;
	int 	start;
	static char	*to_past = NULL;
	int curs2;

	buff = 0;
	line = init_line(prompt);
	if (read(0, &buff, 0) < 0)
		return (NULL);
	ft_prompt(prompt);
	index = 0;
	start = 0;
	curs2 = 0;
	while (1)
	{
		buff = 0;
		read(0, &buff, 4);
	//	fprintf(ttyfd, "%d\n", buff);
		if ((ft_isprint(buff) || buff == ENTER))
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
				break ;
			}
		}
		else
		{
			move_curs(line, buff, &start, &curs2, &to_past);
			navigate_history(line, buff, his_head, &index);
			move_by_word(line, buff);
		}
	}
	fprintf(ttyfd, "------------> line->cmd : |%s|\n", line->str);
	return (line->str);
}
