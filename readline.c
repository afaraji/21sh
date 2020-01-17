/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:00:18 by sazouaka          #+#    #+#             */
/*   Updated: 2020/01/13 22:00:20 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int	termtype(void)
{
	int		ret;
	char	*term_type;
	// int 	column;
	// int		line;

	term_type = getenv("TERM");
	ret = tgetent(NULL, term_type);
	// column = tgetnum("co");
	// line = tgetnum("li");
	if (ret == -1)
	{
		ft_putstr("Could not access the termcap data base.\n");
		return (0);
	}
	else if (ret == 0)
	{
		ft_putstr("Terminal type ");
		ft_putstr(term_type);
		ft_putstr(" is not defined.\n");
		return (0);
	}
	printf("terminal ok [%s]:\n", term_type);
	return (1);
}
/********************************************************/
void	ft_prompt(void)
{
	ft_putstr("\x1B[35m");
	ft_putstr("$> ");
	ft_putstr("\x1b[39m");
}
/********************************************************/
char	*ft_cpy(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}
/********************************************************/
char	*ft_join_pos(char *str, char c, int curs)
{
	int i;
	int j;

	i = 0;
	j = 0;
	char *s1 = malloc(sizeof(char)* (ft_strlen(str) + 2));
	while(i < curs)
	{
		s1[i] = str[i];
		i++;
	}
	s1[i] = c;
	j = curs;
	while(j < (int)ft_strlen(str))
	{
		i++;
		s1[i] = str[j];
		j++;
	}
	if(j == (int)ft_strlen(str))
		i++;
	s1[i]= '\0';
	return(s1);
}
/********************************************************/
int		ft_intputchar(int c)
{
	char ch;

	ch = c;
	return (write(1, &ch ,1));
}
/********************************************************/
void	put_line_curs(t_line *line)
{
	int	i;

	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	i = line->curs;
	while(i < (int)ft_strlen(line->str ))
	{
		ft_putchar(line->str[i]);
		i++;
	}
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
	go_right(line);
}
/********************************************************/
void	read_line(int fd)
{
	int			buff;
	t_line		line;
	int			col;
	int			coef;
	int			i;
	int			j;

	if (fd < 0 || read(fd, &buff, 0) < 0)
		return;
	FILE *ttyfd = fopen("/dev/ttys000", "w");
	line.curs = 0;
	line.str = ft_strdup("");
	col = 3;
	coef = 1;
	j = 0;
	while (1)
	{
		buff = 0;
		read(fd, &buff, 4);
		if (ft_isprint(buff))
		{
			line.str = ft_join_pos(line.str, buff, line.curs);
			col++;
			//fprintf(ttyfd, "------> term_column%d-------> my_col%d\n************\n", tgetnum("co"), col);
			//fprintf(ttyfd, "------>%d\n", i);
			if (col != tgetnum("co") && col != i)
			{
				put_line_curs(&line);
			}
			else if (col == tgetnum("co")|| col == i)
			{
				/************************************************/
        		/***** need to check this part with hajar *******/
        		/************************************************/
				put_line_curs(&line);
				tputs(tgetstr("do", NULL), 1, ft_intputchar);
				coef++;
				i = coef * tgetnum("co");
			}
		}
		else
		{
			fprintf(ttyfd, "------>%d\n", line.curs);
			//fprintf(ttyfd, "------>%x\n", buff);
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
			/**********************************/
    		/****** make next one happen when ther is ' or " ******/
    		/**********************************/
			else if (buff == ENTER && (line.str[line.curs - 1] == 39 || line.str[line.curs - 1] == 34))
			{
				go_down(&line);
				j = 1;
			}
			else if (buff == ENTER && j == 1)
				go_down(&line);
		}
	}
}
/********************************************************/
int	main(int ac, char **av, char **env)
{ 
	struct termios 	s_termios;

	if (termtype())
	{
		if (tcgetattr(0, &s_termios) == -1)
          return (-1);
		s_termios.c_lflag &= ~(ECHO | ICANON);
		if (tcsetattr(0, 0, &s_termios) == -1)
          return (-1);
	}	
	while (1)
	{
		ft_prompt();
		read_line(0);
	}
	(void)ac;
	(void)av;
	(void)env;
	return (0);
}
