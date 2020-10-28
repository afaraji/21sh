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

void	cpy_set_atr_ican(struct termios *src, struct termios *dst)
{
	ft_memcpy(dst->c_cc, src->c_cc, NCCS);
	dst->c_cflag = src->c_cflag;
	dst->c_iflag = src->c_iflag;
	dst->c_ispeed = src->c_ispeed;
	dst->c_oflag = src->c_oflag;
	dst->c_ospeed = src->c_ospeed;
	dst->c_lflag = src->c_lflag & ~(ECHO | ICANON | ISIG);
}

int		ft_set_attr(int index)
{
	static struct termios	old_termios;
	struct termios			s_termios;

	if (!ttyname(0) || !ttyname(1) || !ttyname(2))
		return (2);
	if (index == 0)
	{
		if (!old_termios.c_cflag && !old_termios.c_ospeed)
		{
			if (tcgetattr(0, &old_termios) == -1)
				return (1);
		}
		if (termtype() && check_termcap())
		{
			cpy_set_atr_ican(&old_termios, &s_termios);
			if (tcsetattr(0, 0, &s_termios) == -1)
				return (1);
		}
	}
	else
	{
		if (tcsetattr(0, 0, &old_termios) == -1)
			return (1);
	}
	return (0);
}

void	free_term(t_terminal **term)
{
	if (*term == NULL)
		return ;
	free((*term)->line);
	free((*term)->select);
	free(*term);
	*term = NULL;
}
