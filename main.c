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
#include "parse.h"

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

t_hist	*create_history(void)
{
	char	*file_str;
	t_hist	*his_list = NULL;
	int fd;
	int i;

	if (!(fd = open("./.myshell_history", O_RDONLY | O_CREAT, 0700)))
		return (NULL);
	i = 1;
	while (get_next_line(fd, &file_str) == 1)
		get_his_list(file_str, &his_list, i++);
	close(fd);
	return (his_list);
}

int		ft_exit(int status)
{
	ft_set_attr(1);
	save_list();
	ft_putstr("\nexit\n");
	exit(status);
}

t_variable	*get_env(char *s, int typ)
{
	t_variable	*node;
	int			i;

	i = 0;
	node = (t_variable *)malloc(sizeof(t_variable));
	node->next = NULL;
	node->env = typ;
	while (s && s[i] && s[i] != '=')
		i++;
	node->key = ft_strsub(s, 0, i);
	node->value = ft_strdup(&s[i + 1]);
	node->next = NULL;
	return (node);
}

t_variable	*get_setvar(void)
{
	char		*tmp1;
	char		*tmp2;
	t_variable	*head;

	head = get_env("!=0", 2);
	head->next = get_env("#=0", 2);
	tmp1 = ft_itoa(getpid());
	tmp2 = ft_strjoin("$=", tmp1);
	head->next->next = get_env(tmp2, 2);
	free(tmp1);
	free(tmp2);
	head->next->next->next = get_env("?=0", 2);
	return (head);
}

void	print_set_with_typ(t_variable *list)
{
	t_variable	*node;

	node = list;
	printf("\n++++++++++++++++++++++++\n");
	while (node)
	{
		printf("%d:%s=%s\n", node->env, node->key, node->value);
		node = node->next;
	}
	printf("++++++++++++++++++++++++\n");
		
}

t_variable	*get_set(char **env)
{
	t_variable	*head;
	t_variable	*node;
	int		i;

	head = get_setvar();
	node = head;
	while (node->next)
		node = node->next;
	i = 0;
	while (env && env[i])
	{
		node->next = get_env(env[i], 0);
		node = node->next;
		i++;
	}
	//print_set_with_typ(head);
	return (head);	
}

int		init_shell(char **env)
{
	if (ft_set_attr(0))
		return (1);
	g_var = (t_shell_var){0, 0, NULL, NULL};
	g_var.var = get_set(env);
	g_var.history = create_history();
	return (0);
}

int		main(int ac, char **av, char **env)
{
	char	*line = NULL;
	int		ret = 0;

	ttyfd = fopen("/dev/ttys003", "w");
	if (init_shell(env))
		return (1);
	line = readline(-1);
	while (1)
	{
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			ft_exit(ft_atoi(&line[4]));
		}
		//ret = main_parse(line);
		printf("\n");
		if (line)
			ft_strdel(&line);
		line = readline(ret);
		// fprintf(ttyfd, "------------->(%d) - (%s)\n", ret, line);
	}
	(void)ac;
	(void)av;
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