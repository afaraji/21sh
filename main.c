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

int	create_history(t_hist **his_list)
{
	char	*file_str;
	int fd;
	int i;

	if (!(fd = open("./.myshell_history", O_RDONLY | O_CREAT, 0700)))
		return (-1);
	i = 1;
	while (get_next_line(fd, &file_str) == 1)
		get_his_list(file_str, his_list, i++);
	close(fd);
	return (0);
}

int		ft_exit(t_hist	*his_list, int status)
{
	ft_set_attr(1);
	save_list(his_list);
	ft_putstr("\nexit\n");
	exit(status);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_hist	*his_list = NULL;

	ttyfd = fopen("/dev/ttys003", "w");
	create_history(&his_list);
	if (ft_set_attr(0))
		return (0);
	line = read_line("$> ", &his_list);
	while (1)
	{
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			ft_exit(his_list, ft_atoi(&line[4]));
		}
		line = read_line("\n$> ", &his_list);
	}
	(void)ac;
	(void)av;
	(void)env;
	return (0);
}

// int main(int ac, char **av, char **env)
// {
// 	char	*line;
// 	t_hist	*his_list = NULL;

// 	ttyfd = fopen("/dev/ttys003", "w");
// 	create_history(&his_list);
// 	if (ft_set_attr(0))
// 		return (0);
// 	line = read_line("$> ", &his_list);
// 	while (1)
// 	{
// 		if (ft_strncmp(line, "exit", 4) == 0)
// 		{
// 			ft_exit(his_list, ft_atoi(&line[4]));
// 		}
// 		line = read_line("\n$> ", &his_list);
// 	}
// 	(void)ac;
// 	(void)av;
// 	(void)env;
// 	return (0);
// }