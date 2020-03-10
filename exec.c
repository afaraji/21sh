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

#include "parse.h"



char	**simplecmd_to_tab(t_simple_cmd *cmd)
{

}

int		env_tab_count(void)
{
	t_variable	*node;
	int			count;
	
	node = g_var.var;
	count = 0;
	while (node)
	{
		if (node->env == 0)
			count++;
		node = node->next;
	}
	return (count);
}

char	**env_to_tab(void)
{
	t_variable	*node;
	char		**argv;
	char		*tmp;
	int			i;
	
	node = g_var.var;
	i = env_tab_count();	
	if (!(argv = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (node)
	{
		if (node->env == 0)
		{
			tmp = ft_strjoin(node->key, "=");
			argv[i] = ft_strjoin(tmp, node->value);
			free(tmp);
			i++;
		}
		node = node->next;
	}
	argv[i] = NULL;
	if (i == 0)
		return (NULL);
	return (argv);
}

int		execute(t_cmdlist *cmd)
{
	while (cmd)
	{
		//fork
		exec_and_or(cmd->and_or);
		if (parent && cmd->bg)
		{
			// wait pid
		}
		cmd = cmd->next;
	}
}

/*
int		runcmd(char *path, char **argv, char **env_tab)
{
	pid_t	child_pid;
	int		child_status;
	pid_t	tpid;

	if (access(path, X_OK) != 0 || verify_type(path) != 2)
	{
		ft_putstr(argv[0]);
		ft_putstr(": Permission denied.\n");
		return (-1);
	}
	child_pid = fork();
	if (child_pid == 0)
	{
		execve(path, argv, env_tab);
		return (0);
	}
	else
	{
		tpid = wait(&child_status);
		while (tpid != child_pid)
		{
			tpid = wait(&child_status);
		}
		return (child_status);
	}
}

char	*valid_cmd_2(char **cmd, char **paths)
{
	int		i;
	char	*path;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd[0]);
		if (access(path, F_OK) == 0)
		{
			free_tab(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

char	*valid_cmd(char **cmd, t_env *head)
{
	char	**paths;

	if (access(cmd[0], F_OK) == 0 && verify_type(cmd[0]) == 2 && ispth(cmd[0]))
		return (ft_strdup(cmd[0]));
	paths = paths_from_env(head);
	if (paths == NULL || verify_type(cmd[0]) == 1 || ispth(cmd[0]))
	{
		free_tab(paths);
		return (NULL);
	}
	return (valid_cmd_2(cmd, paths));
}

int		run_cmd(char **cmd, t_env *head)
{
	char *path;
	char **env_tab;

	path = valid_cmd(cmd, head);
	if (path != NULL)
	{
		env_tab = list_to_tab(head);
		runcmd(path, cmd, env_tab);
		free_tab(env_tab);
		free(path);
		return (0);
	}
	else
	{
		if (!access(cmd[0], F_OK) && verify_type(cmd[0]) != 2 && ispth(cmd[0]))
		{
			ft_putstr(cmd[0]);
			ft_putstr(": Permission denied.\n");
			return (-2);
		}
		ft_putstr("minishell: command not found: ");
		ft_putstr(cmd[0]);
		ft_putstr("\n");
		return (-1);
	}
}
*/