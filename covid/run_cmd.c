/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 01:27:47 by afaraji           #+#    #+#             */
/*   Updated: 2019/12/05 01:27:49 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	free_tab(char **table)
{
	int i;

	i = 0;
	if (table == NULL)
		return ;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

int		verify_type_me(char *str) // 0:no file or permission| 1:dir | 2:file | -2:slink
{
	struct stat	st;
	int			ret;
	DIR			*d;

	if ((ret = lstat(str, &st)) == 0)
	{
		if (S_ISDIR(st.st_mode) || S_ISLNK(st.st_mode))
		{
			if ((d = opendir(str)) == NULL)
				return (-2);
			closedir(d);
			return (1);
		}
		else
			return (2);
	}
	return (0);
}

int		runcmd(char *path, char **argv, char **env_tab)
{
	pid_t	child_pid;
	int		child_status;
	pid_t	tpid;

	if (access(path, X_OK) != 0 || verify_type_me(path) != 2)
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

char	*valid_cmd(char **cmd)
{
	char	**paths;

	if (access(cmd[0], F_OK) == 0 && verify_type_me(cmd[0]) == 2 && ft_strchr(cmd[0], '/'))
		return (ft_strdup(cmd[0]));
	paths = paths_from_env();
	if (paths == NULL || verify_type_me(cmd[0]) == 1 || ft_strchr(cmd[0], '/'))
	{
		free_tab(paths);
		return (NULL);
	}
	return (valid_cmd_2(cmd, paths));
}

int		run_cmd(char **cmd)
{
	char *path;
	char **env_tab;

	path = valid_cmd(cmd);
	if (path != NULL)
	{
		env_tab = env_to_tab();
		runcmd(path, cmd, env_tab);
		free_tab(env_tab);
		free(path);
		return (0);
	}
	else
	{
		if (!access(cmd[0], F_OK) && verify_type_me(cmd[0]) != 2 && ft_strchr(cmd[0], '/'))
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
