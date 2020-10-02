/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:13:41 by afaraji           #+#    #+#             */
/*   Updated: 2020/02/10 16:14:17 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"
#include "covid_ast.c"

int		ft_exit(int status)
{
	ft_putstr("\nexit\n");
	exit(status);
}


int		main(int ac, char **av, char **env)
{
	char	*line = NULL;
	int		ret = 0;
	t_cmdlist		*cmd;
	t_cmdlist		*node;

	if (ac != 2)
		return (1);
	line = ft_strdup(av[1]);

	if (ft_strncmp(line, "exit", 4) == 0)
		ft_exit(ft_atoi(&line[4]));
	// ret = main_parse(line);
	printf("[%s]\n", line);
	ttyfd = fopen("/dev/ttys001", "w");
	cmd = covid_main_parse(line);
	int i = 0;
	node = cmd;
	while (node)
	{
		fprintf(ttyfd, "++++++++++ (cmd: %d | BG: %d) ++++++++++\n", i, node->bg);
		i++;
		print_andor(node);
		node = node->next;
	}
	
	
	return (0);
}