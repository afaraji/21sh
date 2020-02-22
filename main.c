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
	
// 	node = his_head;
// 	while (node)
// 	{
// 		fprintf(ttyfd, "\n\n------------> history : |%s|\n", node->hist_str);
// 		node = node->next;
// 	}
// }


int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*file_str;
	t_hist	*his_list = NULL;
	int fd;
	char	*buff;

	buff = NULL;
	ttyfd = fopen("/dev/ttys003", "w");
	fd = open(ft_strjoin(getcwd(buff, 500) , "/.myshell_history"), O_RDONLY);
	if (fd < 0)
		return (-1);
	else
	{
		int i = 1;
		while (get_next_line(fd, &file_str))
			get_his_list(file_str, &his_list, i++);
		close(fd);
	}
	if (ft_set_attr())
		return (0);
	fd = open(ft_strjoin(getcwd(buff, 500) , "/.myshell_history"), O_WRONLY);
	while (1)
	{
		line = read_line("\n$> ", &his_list);
		//print_list(his_list);
		if (ft_strcmp(line, "exit") == 0)
		{
			save_list(his_list, fd);
			return 0;
		}
	}
	close(fd);
	(void)ac;
	(void)av;
	(void)env;
	return (0);
}
