/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_curs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 22:30:54 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/12 22:30:56 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char	*select_copy_char(t_line *line, int curs)
{
	int	i;
	int j;
	char	*to_copy;

	to_copy = (char *)malloc(sizeof(char) * curs + 1);
	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	i = line->curs;
	j = 0;
	while (i <= curs)
	{
		to_copy[j] = line->str[i];
		ft_putchar(line->str[i]);
		i++;
		j++;
	}
	to_copy[j] = '\0';
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
	return (to_copy);
}

void	display_line3(t_line *line)
{
	int	i;

	fprintf(ttyfd, "****\n");
	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	i = 0;
	while (i < (int)ft_strlen(line->str))
	{
		ft_putchar(line->str[i]);
		i++;
	}
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
}
/***************************************************/
void	past_char(t_line *line)
{
	int	i;

	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	i = 0;
	while (i < (int)ft_strlen(line->str))
	{
		//sleep(1);
		ft_putchar(line->str[i]);
		i++;
	}
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
}


char	*join_str(t_line *line, char *to_past)
{
	int curs;
	char	*tmp1;
	char	*tmp2;
	char	*str;

	curs = line->curs;
	tmp1 = ft_strsub(line->str, 0, curs);
	//fprintf(ttyfd, "tmp1: %s\n", tmp1);
	tmp2 = ft_strjoin(tmp1, to_past);
	//fprintf(ttyfd, "tmp2: %s\n", tmp2);
	str = ft_strjoin(tmp2, &line->str[curs]);
	//fprintf(ttyfd, "str: %s\n", str);
	return(str);
}

void	move_curs(t_line *line, int buff, int *start, int *curs, char **to_past)
{
	//fprintf(ttyfd, "%X\n", buff);
	//fprintf(ttyfd, "to-past : %s,  curs : %d\n", to_past, *curs);
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
	else if (buff == UPLINE)
		go_up(line);
	else if (buff == DWNLINE)
		go_down(line);
	else if (buff == SELECT)
	{
		if (*start == 1)
		{
			tputs(tgetstr("mr", NULL), 1, ft_intputchar);
			//fprintf(ttyfd, "to-past : %s,  curs : %d\n", to_past, *curs);
			*to_past = ft_strdup(select_copy_char(line, *curs));
			tputs(tgetstr("me", NULL), 1, ft_intputchar);
			while (line->curs <= *curs)
				go_right(line);
			display_line(line);
			*start = 0;
			//go_end(line);
		}
		else if (*start == 0)
		{
			//fprintf(ttyfd, "line->str  :  |%s|  , to-past : %s,  curs : %d\n",line->str , *to_past, *curs);
			*curs = line->curs;
			*start = 1;
		}
		
	}
	else if (buff == COPY && *to_past)
	{
		line->str = join_str(line, *to_past);
		//fprintf(ttyfd, "line->str : %s\n", line->str);
		int i;

		i = line->curs + (int)ft_strlen(*to_past);
		while (line->curs > 0)
		{
			//sleep(1);
			go_left(line);
		}
		past_char(line);
		//fprintf(ttyfd, "%d\n", (int)ft_strlen(line->str) - (int)ft_strlen(*to_past));
		while (line->curs < i)
		{
			go_right(line);
		}
	}
}
