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

t_hist	*get_his_node(char *file_str, t_hist *prec)
{
	t_hist	*node;

	node = (t_hist *)malloc(sizeof(t_hist));
	node->hist_str = file_str;
	node->next = NULL;
	node->prec = prec;
	return(node);	
}

void	get_his_list(char *file_str, t_hist **head)
{
	t_hist	*node;

	if (!(*head))
	{
		node = get_his_node(file_str, NULL);
		*head = node;
	}
	else
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = get_his_node(file_str, node);
	}
	
}

void	print_list(t_hist *his_head)
{
	t_hist	*node;
	
	node = his_head;
	while (node)
	{
		fprintf(ttyfd, "\n\n------------> history : |%s|\n", node->hist_str);
		node = node->next;
	}
}

void	save_list(t_hist *his_head, int fd)
{
	t_hist	*node;
	
	node = his_head;
	while (node)
	{
		ft_putstr_fd(node->hist_str, fd);
		ft_putchar_fd('\n', fd);
		node = node->next;
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*file_str;
	t_hist	*his_list = NULL;
	int fd;

	ttyfd = fopen("/dev/ttys002", "w");
	fd = open("/Users/samira/Desktop/21sh/.myshell_history", O_RDONLY);
	if (fd < 0)
		return (-1);
	else
	{
		while (get_next_line(fd, &file_str))
			get_his_list(file_str, &his_list);
		close(fd);
	}
	if (ft_set_attr())
		return (0);
	fd = open("/Users/samira/Desktop/21sh/.myshell_history", O_WRONLY);
	while (1)
	{
		line = read_line("$> ", &his_list);
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
