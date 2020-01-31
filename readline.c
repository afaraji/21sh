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


/**********************************************************/
/****** 1- curs need to go up when delet on multiline *****/
/****** 2- find a solution for copy past with mouse *******/
/**********************************************************/
t_line	*init_line(char *prompt)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	line->curs = 0;
	line->cmd = ft_strdup("");
	line->str = ft_strdup("");
	line->pmt_s = ft_strlen(prompt);
	line->col = tgetnum("co");
	return (line);
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
void	is_dquote(t_line *line)
{
	ft_prompt("dquote> ");
	line->curs = 0;
	line->cmd = ft_strjoin(line->cmd, line->str);
	line->str = ft_strdup("");
}
/*********************************************************/
void	is_quote(t_line *line)
{
	ft_prompt("quote> ");
	line->curs = 0;
	line->cmd = ft_strjoin(line->cmd, line->str);
	line->str = ft_strdup("");
}
/*********************************************************/
int	get_cmd(t_line *line, char buff, int *j)
{
	line->str = join_line(line->str, buff, line->curs);
	display_line(line);
	go_right(line);
	if (buff == ENTER && *j == 0)
	{
		line->cmd = ft_strjoin(line->cmd, line->str);
		return(1);
	}
	fprintf(ttyfd, "+++++buff:%d+++j=%d\n", buff, *j);
	if (buff == 34 && *j == 0)
		*j = 1;
	else if (buff == 39 && *j == 0)
		*j = 2;
	else if (buff == 34 && *j == 1)
		*j = 0;
	else if (buff == 39 && *j == 2)
		*j = 0;
	else if (buff == ENTER && *j == 1)
		is_dquote(line);
	else if (buff == ENTER && *j == 2)
		is_quote(line);
	return (0);
}
/*********************************************************/
void move_curs( t_line *line, int buff)
{
	if (buff == LFTARROW)
		go_left(line);
	else if (buff == RTARROW)
		go_right(line);
	else if (buff == DEL)
		del_char(line);
	else if (buff == HOME)
		go_home(line);
	else if (buff == END)
		go_end(line);

}
/*********************************************************/
char	*read_line(char *prompt)
{
	int		buff;
	t_line		*line;
	int j;

	j = 0;
	buff = 0;
	line = init_line(prompt);
	if (read(0, &buff, 0) < 0)
		return(NULL);
	ft_prompt(prompt);
	while (1)
	{
		buff = 0;
		read(0, &buff, 4);
		if ((ft_isprint(buff) || buff == ENTER))
		{
			if (get_cmd(line, buff, &j) == 1)
				break;
		}
		else
			move_curs(line, buff);
	}
	fprintf(ttyfd, "------------------------> line.cmd : %s------------------------> line.str : %s", line->cmd, line->str);
	return (line->cmd);
}
