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

int		exec(t_pipe_seq *cmd)
{
	int fd[2];
	pid_t	pid_l;
	pid_t	pid_r;


	if(pipe(fd) != 0)
		return (-1);
	if ((pid_l = fork()) == -1)
		return (-1);//should set errno
	if ((pid_r = fork()) == -1)
		return (-1);//should set errno
	if (pid_l == 0)
	{
		//left child
		if(cmd->left == NULL)//could be NULL ? or it s never NULL;
			return (0);
		close(fd[1]);
		dup2(3,1);
		close(3);
		exit(exec_ve(cmd->left));
	}
	if (pid_r == 0)
	{
		//right child
		if(cmd->right == NULL)//what should do if no more elemnts
			return (0);
		close(fd[0]);
		dup2(4,0);
		close(4);
		exit(exec(cmd->right));
	}
	if (pid_l > 0 && pid_r > 0)
	{
		//parent
		close(fd[0]);
		close(fd[1]);
		waitpid(pid_l);
		waitpid(pid_r);
	}
	return (0);	
}

int		execute(t_and_or *cmd)
{
	while(cmd)
	{
	//	if cmd->dependent is OK continue if not return 1
		if(cmd->ast)
			exec(cmd->ast);
		cmd = cmd->next;
	}
	return (0);
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
	node = cmd;
	while (node)
	{
		execute(node->and_or);
		node = node->next;
	}
	
	return (0);;
}