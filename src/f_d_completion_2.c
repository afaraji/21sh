/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_d_completion_2.c                                 :+:      :+:    :+:   */
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

char			*matched_f_d_1(struct dirent *dir)
{
	char	*tmp;

	tmp = ft_strjoin("./", dir->d_name);
	if (verify_type(tmp) == 1 || verify_type(tmp) == 3)
	{
		ft_strdel(&tmp);
		return (ft_strjoin(dir->d_name, "/"));
	}
	else
	{
		ft_strdel(&tmp);
		return (ft_strdup(dir->d_name));
	}
	if (tmp)
		ft_strdel(&tmp);
	return (NULL);
}

void			get_f_d_list(t_l **f_d_list, char **tmp, t_l **node)
{
	if (!(*f_d_list))
	{
		*f_d_list = names_list(*tmp);
		if (*tmp)
			ft_strdel(tmp);
		*node = *f_d_list;
	}
	else
	{
		(*node)->next = names_list(*tmp);
		if (*tmp)
			ft_strdel(tmp);
		*node = (*node)->next;
	}
}

t_l				*matched_f_d(DIR *d, char *str)
{
	struct dirent	*dir;
	char			*tmp;
	t_l				*f_d_list;
	t_l				*node;

	f_d_list = NULL;
	node = NULL;
	tmp = NULL;
	while ((dir = readdir(d)))
	{
		tmp = matched_f_d_1(dir);
		if (!ft_strcmp("", str)
		|| !ft_strncmp(dir->d_name, str, ft_strlen(str)))
		{
			get_f_d_list(&f_d_list, &tmp, &node);
		}
		if (tmp)
			ft_strdel(&tmp);
	}
	return (f_d_list);
}

t_l				*matched_files_dirs(char *str)
{
	DIR	*d;
	t_l	*files_dirs_list;

	files_dirs_list = NULL;
	d = NULL;
	d = opendir(".");
	if (d != NULL)
	{
		files_dirs_list = matched_f_d(d, str);
	}
	closedir(d);
	return (files_dirs_list);
}
