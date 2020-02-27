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

// void	print_list(t_hist *his_head)
// {
// 	t_hist	*node;

// 	fprintf(ttyfd, "*** got here\n");
// 	node = his_head;
// 	while (node)
// 	{
// 		fprintf(ttyfd, "\n\n------------> history : |%s|\n", node->hist_str);
// 		node = node->next;
// 	}
// }

int	main(int ac, char **av, char **env)
{
	struct termios	s_termios;
	struct termios	old_termios;
	char	*line;
	char	*file_str;
	t_hist	*his_list = NULL;
	int fd;
	char	*buff;

	buff = NULL;
	ttyfd = fopen("/dev/ttys002", "w");
	tcgetattr(0, &old_termios);
	if (!(fd = open("./.myshell_history", O_RDONLY | O_CREAT, 0700)))
		return (-1);
	else
	{
		int i = 1;
		while (get_next_line(fd, &file_str) == 1)
			get_his_list(file_str, &his_list, i++);
		close(fd);
	}
	if (ft_set_attr(&s_termios))
		return (0);
	if (!(fd = open("./.myshell_history", O_WRONLY)))
		return (-1);
	line = read_line("$> ", &his_list);
	while (1)
	{
		if (ft_strcmp(line, "exit") == 0)
		{
			tcsetattr(0, 0, &old_termios);
			save_list(his_list, fd);
			ft_putstr("\nexit\n");
			return 0;
		}
		line = read_line("\n$> ", &his_list);
	}
	close(fd);
	(void)ac;
	(void)av;
	(void)env;
	return (0);
}
