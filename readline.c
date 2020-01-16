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

	if (fd < 0 || read(fd, &buff, 0) < 0)
		return;
	FILE *ttyfd = fopen("/dev/ttys001", "w");
	line.curs = 0;
	line.str = ft_strdup("");
	while (1)
	{
		buff = 0;
		read(fd, &buff, 4);
		if (ft_isprint(buff))
		{
			line.str = ft_join_pos(line.str, buff, line.curs);
			put_line_curs(&line);
		}
		else
		{
			fprintf(ttyfd, "------>%x\n", buff);
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
			else if (buff == ENTER)
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