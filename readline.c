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


/*********************************************************/
/***** 1- find a solution for copy past with mouse *******/
/***** 2- make a function to manage multiple lines *******/
/***** 3- fixe the problem with curs when u work on terminal *******/
/*********************************************************/
void	init_line(t_line *line, char *prompt)
{
	line->curs = 0;
	line->cmd = ft_strdup("");
	line->str = ft_strdup("");
	line->pmt_s = ft_strlen(prompt);
	line->col = tgetnum("co");
}
/*********************************************************/
void	ft_prompt(char *prompt)
{
	ft_putstr("\x1B[35m");
	ft_putstr(prompt);
	ft_putstr("\x1b[39m");
}
/*********************************************************/
void	display_line(t_line *line)
{
	int	i;

	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	i = line->curs;
	while(i < (int)ft_strlen(line->str))
	{
		ft_putchar(line->str[i]);
		i++;
	}
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
}
/*********************************************************/
char	*read_line(char *prompt)
{
	int		buff;
	t_line		line;
	int j;

	buff = 0;
	j = 0;
	init_line(&line, prompt);
	if (read(0, &buff, 0) < 0)
		return(NULL);
	ft_prompt(prompt);
	while (1)
	{
		buff = 0;
		read(0, &buff, 4);
		if ((ft_isprint(buff) || buff == ENTER))
		{
			line.str = join_line(line.str, buff, line.curs);
			display_line(&line);
			go_right(&line);
			if (buff == ENTER && j == 0)
			{
				fprintf(ttyfd, "----  line.str |%s|\n", line.str);
				line.cmd = ft_strjoin(line.cmd, line.str);
				fprintf(ttyfd, "----  line.cmd |%s|\n", line.cmd);
			 	break;
			}
			if (buff == 34 && j == 0)
			 	j = 1;
			else if (buff == 39 && j == 0)
			 	j = 2;
			else if (buff == 34 && j == 1)
			 	j = 0;
			else if (buff == 39 && j == 2)
			 	j = 0;
			else if (buff == ENTER && j == 1)
			{
			 	ft_prompt("dquote> ");
				line.curs = 0;
				line.cmd = ft_strjoin(line.cmd, line.str);
				line.str = ft_strdup("");
			}
			else if (buff == ENTER && j == 2)
			{
			 	ft_prompt("quote> ");
				line.curs = 0;
				line.cmd = ft_strjoin(line.cmd, line.str);
				line.str = ft_strdup("");
			}
		}
		else
		{
			if (buff == LFTARROW)
				go_left(&line);
			else if (buff == RTARROW)
				go_right(&line);
			else if (buff == DEL)
				del_char(&line);
			else if (buff == HOME)
				go_home(&line);
			else if (buff == END)
				go_end(&line);
		}
	}
	fprintf(ttyfd, "------------------------> line.cmd : %s------------------------> line.str : %s", line.cmd, line.str);
	return (line.cmd);
}
