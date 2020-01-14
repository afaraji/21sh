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

#include "21sh.h"

int	main(int ac, char **av, char **env)
{
	int		ret;
	char	*term_type;

	term_type = getenv("TERM");

	ret = tgetent(NULL, term_type);

	if (ret == -1)
		ft_putstr("Could not access the termcap data base.\n");
	else if (ret == 0)
	{
		ft_putstr("Terminal type ");
		ft_putstr(term_type);
		ft_putstr(" is not defined.\n");
	}
	ft_putstr("lol\n");
	(void)ac;
	(void)av;
	(void)env;
	return (0);
}