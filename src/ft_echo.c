/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:36:18 by sazouaka          #+#    #+#             */
/*   Updated: 2019/12/05 16:36:20 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"

int	ft_echo(char **av)
{
	int	i;

	if (!check_fd(1,1))
	{
		ft_putstr_fd("shell: echo: write error: Bad file descriptor\n", 2);
		return (1);
	}
	i = 1;
	if (av[1] == NULL)
	{
		ft_putchar('\n');
		return (0);
	}
	if (av[1] && ft_strcmp(av[1], "-n") == 0)
		i++;
	while (av[i])
	{
		ft_putstr(av[i]);
		if (av[i + 1] != NULL)
			ft_putchar(' ');
		i++;
	}
	if (ft_strcmp(av[1], "-n") == 0)
		return (0);
	else
		ft_putchar('\n');
	return (0);
}
