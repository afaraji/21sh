/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 19:35:04 by sazouaka          #+#    #+#             */
/*   Updated: 2020/01/18 19:35:05 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		check_termcap(void)
{
	if (!(tgetstr("nd", NULL)) || !(tgetstr("sc", NULL))
	|| !(tgetstr("rc", NULL)) || !(tgetstr("cd", NULL))
	|| !(tgetstr("up", NULL)) || !(tgetstr("ch", NULL))
	|| !(tgetstr("le", NULL)) || !(tgetstr("do", NULL)))
	{
		ft_putstr("NULL TERMCAP\n");
		return (0);
	}
	else
		return (1);
}

int		termtype(void)
{
	int		ret;
	char	*term_type;

	term_type = getenv("TERM");
	ret = tgetent(NULL, term_type);
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
	return (1);
}

int		ft_set_attr(int index)
{
	static struct termios	old_termios;
	struct termios			s_termios;

	if (index == 0)
	{
		tcgetattr(0, &old_termios);
		if (termtype() && check_termcap())
		{
			if (tcgetattr(0, &s_termios) == -1)
				return (1);
			s_termios.c_lflag &= ~(ECHO | ICANON);
			if (tcsetattr(0, 0, &s_termios) == -1)
				return (1);
		}
		else
			return (1);
	}
	else
	{
		tcsetattr(0, 0, &old_termios);
		return (1);
	}
	return (0);
}

void	free_term(t_terminal **term)
{
	free((*term)->line);
	free((*term)->select);
	free(*term);
}
