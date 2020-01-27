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

int	main(int ac, char **av, char **env)
{
	char	*line;

	ttyfd = fopen("/dev/ttys000", "w");
	if (ft_set_attr())
		return (0);
	while (1)
		line = read_line("$> ");
	(void)ac;
	(void)av;
	(void)env;
	return (0);
}
