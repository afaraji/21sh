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
	int 	column;
	int		line;

	term_type = getenv("TERM");
	ret = tgetent(NULL, term_type);
	column = tgetnum("co");
	line = tgetnum("li");
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

void	ft_prompt(void)
{
	ft_putstr("\x1B[35m");
	ft_putstr("$> ");
	ft_putstr("\x1b[39m");
}

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

char	*ft_join_pos(char *str, char c, int curs)
{
	int i;

	if (str == NULL)
	{
		str = (char *)malloc(sizeof(char) + 1);
		str[0] = c;
		str[1] = '\0';
	}
	else
	{
		i = 0;
		while (i <= 2)
			i++;
		str[i] = c;
		str = ft_strjoin(str, &str[curs + 1]);
	}
	return(str);
}

void	go_right(int curs)
{
	char	*cm_cap;

	cm_cap = tgetstr("cm", NULL);
	tputs(tgoto(cm_cap, curs, 0), 1, putchar);
}

void	read_line(int fd)
{
	int			buff;
	t_line			line;
	char			*cm_cap;

	if (fd < 0 || read(fd, &buff, 0) < 0)
		return;
	FILE *ttyfd = fopen("/dev/ttys003", "w");
	while (1)
	{
		buff = 0;
		read(fd, &buff, 4);
		// buff = buff & 0x00000FF;
		line.curs = 0;
		line.str = NULL;
		if (ft_isprint(buff))
		{
			line.str = ft_join_pos(line.str, (char)buff, line.curs);
			ft_putstr(line.str);
			line.curs++;
			go_right(line.curs);
		}
		else
		{
			//***************************//
			// fixe this part//
			//********************//
			fprintf(ttyfd, "------>%x\n", buff);
			if (buff == LFTARROW)
			{
				cm_cap = tgetstr("cm", NULL);
				tputs(tgoto(cm_cap, (line.curs - 1), 1), 1, putchar);
			}
		}
	}
}

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
	t_line line;
	line.curs = 0;
	line.str = NULL;
	
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