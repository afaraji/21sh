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
/****** - find a solution for copy past with mouse *******/
/****************************************************************/

t_line	*init_line(char *prompt)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	line->curs = 0;
//	line->cmd = ft_strdup("");
	line->str = ft_strdup("");
	line->pmt_s = ft_strlen(prompt) + 1;
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
	//fprintf(ttyfd, "line->str : |%s|\n", line->str);
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
int	printable_char(t_line	*line, t_hist **his_head, int buff)
{
	int	curs;

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
			return(1);
		}
	}
	return (0);
}

char	*read_line(char *prompt, t_hist **his_head)
{
	int		buff;
	t_line	*line;
	int		index;
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
		if (printable_char(line, his_head, buff))
			break;
		if (!(ft_isprint(buff)))
		{
			if (buff == SELECT)
			{
				select->len = 0;
				select->on = 1;
				select->start = line->curs;
			}
			else if (buff == COPY)
				ft_copy(line, select, &to_past);
			else if (buff == PAST && to_past)
				past(line, &to_past);
			else
			{
				move_curs(line, buff, select);
				navigate_history(line, buff, his_head, &index);
				move_by_word(line, buff);
			}
		}
	}
	fprintf(ttyfd, "+++ line->str : |%s|\n", line->str);
	return (line->str);
}


/*************************** nounous ****************************

char	*ft_copy(t_line *line)
{
	int buff;

	buff = 0;
	read(0, &buff, 4);
	while ()
	{
		
	}
	

}


char	*read_line(char *prompt, t_hist **his_head)
{
	int		buff;
	t_line	*line;
	int		index;
	int 	start;
	static char	*to_past = NULL;
	int curs;

	buff = 0;
	index = 0;
	start = 0;
	curs = 0;
	line = init_line(prompt);
	if (read(0, &buff, 0) < 0)
		return (NULL);
	ft_prompt(prompt);
	while (1)
	{
		buff = 0;
		read(0, &buff, 4);fprintf(ttyfd,"+-+-+>%X\n", buff);
		if (printable_char(line, his_head, buff))
			break;
		if (!(ft_isprint(buff)))
		{
			if (buff == SELECT)
				to_past = ft_copy(line);
			else if (buff == PAST)
				ft_past();
			else
			{
				move_curs(line, buff);
				navigate_history(line, buff, his_head, &index);
				move_by_word(line, buff);
			}
		}
	}
	return (line->str);
}

************************************************************/
