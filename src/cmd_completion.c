/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 19:33:46 by sazouaka          #+#    #+#             */
/*   Updated: 2020/10/02 19:33:48 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

void			cmd_path_1(char **tmp, char ***cmd_paths)
{
	int	i;

	i = 0;
	while (tmp[i])
		i++;
	if (!(*cmd_paths = (char **)malloc(sizeof(char *) * (i + 1))))
		return ;
	i = 0;
	while (tmp[i])
	{
		(*cmd_paths)[i] = ft_strjoin(tmp[i], "/");
		ft_strdel(&tmp[i]);
		i++;
	}
	free(tmp);
	(*cmd_paths)[i] = NULL;
}

int				cmd_path(t_l *cmd_list, char ***cmd_tab, char ***cmd_paths)
{
	char	**tmp;

	tmp = NULL;
	get_path_value(&tmp);
	if (tmp == NULL)
	{
		if (cmd_list)
			*cmd_tab = tab_from_list(sort_list(cmd_list));
		else
		{
			if (!(*cmd_tab = (char **)malloc(sizeof(char *) * 1)))
				return (0);
			(*cmd_tab)[0] = NULL;
		}
		return (1);
	}
	else if (tmp != NULL)
	{
		cmd_path_1(tmp, cmd_paths);
		return (2);
	}
	return (0);
}

void			get_cmd_list(t_l **cmd_list, char **cmd_paths, char *str)
{
	int				i;
	DIR				*d;
	struct dirent	*dir;

	i = 0;
	d = NULL;
	while (cmd_paths[i])
	{
		d = opendir(cmd_paths[i]);
		if (d)
		{
			while ((dir = readdir(d)))
			{
				if (!ft_strncmp(str, dir->d_name, ft_strlen(str))
				&& ft_strcmp(dir->d_name, ".")
				&& ft_strcmp(dir->d_name, ".."))
				{
					*cmd_list = get_cmd_list_1(dir->d_name, *cmd_list);
				}
			}
			closedir(d);
		}
		i++;
	}
}

char			**cmd_search(char *str)
{
	char	**cmd_paths;
	t_l		*cmd_list;
	char	**cmd_tab;

	cmd_paths = NULL;
	cmd_tab = NULL;
	cmd_list = search_builtin(str);
	if (cmd_path(cmd_list, &cmd_tab, &cmd_paths) == 1)
	{
		free_list(cmd_list);
		free_tab(cmd_paths);
		return (cmd_tab);
	}
	get_cmd_list(&cmd_list, cmd_paths, str);
	free_tab(cmd_paths);
	if (!cmd_list)
	{
		if (!(cmd_tab = (char **)malloc(sizeof(char *) * 1)))
			return (NULL);
		cmd_tab[0] = NULL;
	}
	else
		cmd_tab = tab_from_list(sort_list(cmd_list));
	free_list(cmd_list);
	return (cmd_tab);
}
