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
/***** 3- make a func for line reaching termin end *******/
/*********************************************************/
void	init_line(t_line *line, char *prompt)
{
	line->curs = 0;
	line->str = ft_strdup("");
	line->prompt_size = ft_strlen(prompt);
}

void	ft_prompt(char *prompt)
{
	ft_putstr("\x1B[35m");
	ft_putstr(prompt);
	ft_putstr("\x1b[39m");
}

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

char	*read_line(char *prompt)
{
	int		buff;
	t_line		line;
	int			coef;
	int			j;

	buff = 0;
	init_line(&line, prompt);
	if (read(0, &buff, 0) < 0)
		return(NULL);
	coef = 1;
	j = 0;
	ft_prompt(prompt);
	while (1)
	{
		buff = 0;
		read(0, &buff, 4);
		if (ft_isprint(buff) || buff == ENTER)
		{
			line.str = join_line(line.str, buff, line.curs);
			display_line(&line);
			go_right(&line);
			if(buff == ENTER)
				break;
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
	return (line.str);
}
