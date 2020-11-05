/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_d_completion.c                                   :+:      :+:    :+:   */
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

char			**files_dirs_search_4(t_l *files_dirs_list)
{
	char	**dir_tab;

	dir_tab = NULL;
	if (files_dirs_list)
	{
		dir_tab = tab_from_list(sort_list(files_dirs_list));
		free_list(files_dirs_list);
	}
	else
	{
		if (!(dir_tab = (char **)malloc(sizeof(char *) * 1)))
			return (NULL);
		dir_tab[0] = NULL;
	}
	return (dir_tab);
}

char			*files_dirs_search_3(char *d_name, char *path)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	if (!(ft_strcmp(path, ".")))
	{
		tmp1 = ft_strjoin(path, "/");
		tmp2 = ft_strjoin(tmp1, d_name);
		ft_strdel(&tmp1);
	}
	else
		tmp2 = ft_strjoin(path, d_name);
	if (verify_type(tmp2) == 1 || verify_type(tmp2) == 3)
	{
		ft_strdel(&tmp2);
		tmp1 = ft_strjoin(d_name, "/");
	}
	else
	{
		ft_strdel(&tmp2);
		tmp1 = ft_strdup(d_name);
	}
	return (tmp1);
}

char			**files_dirs_search_2(char *path)
{
	char	**dir_tab;
	t_l		*files_dirs_list;

	files_dirs_list = matched_files_dirs(path);
	if (path)
		ft_strdel(&path);
	dir_tab = NULL;
	if (files_dirs_list)
	{
		dir_tab = tab_from_list(sort_list(files_dirs_list));
		free_list(files_dirs_list);
	}
	else
	{
		if (!(dir_tab = (char **)malloc(sizeof(char *) * 1)))
			return (NULL);
		dir_tab[0] = NULL;
	}
	return (dir_tab);
}

char			**files_dirs_search_1(char *path, char *to_cmp, DIR *d)
{
	struct dirent	*dir;
	char			*file_dir;
	t_l				*files_dirs_list;
	t_l				*node;

	init_vars(&files_dirs_list, &file_dir, &node);
	while ((dir = readdir(d)))
	{
		file_dir = files_dirs_search_3(dir->d_name, path);
		if (!files_dirs_list)
		{
			files_dirs_list = f_d_search(path, dir->d_name, to_cmp, file_dir);
			node = files_dirs_list;
			free_file_dir(&file_dir);
		}
		else
		{
			node->next = f_d_search(path, dir->d_name, to_cmp, file_dir);
			if (node->next)
				node = node->next;
			free_file_dir(&file_dir);
		}
	}
	closedir(d);
	return (files_dirs_search_4(files_dirs_list));
}

char			**files_dirs_search(char *str)
{
	DIR		*d;
	char	*to_cmp;
	char	*path;
	char	**files_dirs;

	path = get_path(str);
	to_cmp = get_to_cmp(str);
	files_dirs = NULL;
	d = NULL;
	d = opendir(path);
	if (d != NULL)
	{
		files_dirs = files_dirs_search_1(path, to_cmp, d);
		if (path)
			ft_strdel(&path);
		if (to_cmp)
			free(to_cmp);
		return (files_dirs);
	}
	else
	{
		if (to_cmp)
			free(to_cmp);
		return (files_dirs_search_2(path));
	}
}
