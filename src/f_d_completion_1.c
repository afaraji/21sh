/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_d_completion_1.c                                 :+:      :+:    :+:   */
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

t_l		*names_list(char *str)
{
	t_l	*node;

	if (!(node = (t_l *)malloc(sizeof(t_l))))
		return (NULL);
	node->data = ft_strdup(str);
	node->next = NULL;
	return (node);
}

t_l		*f_d_search(char *path, char *d_name, char *cmp, char *f_d)
{
	t_l		*list;

	list = NULL;
	if (path[0] == '.')
	{
		if (ft_strcmp(d_name, ".") && ft_strcmp(d_name, ".."))
		{
			if ((!ft_strcmp("", cmp) ||
			!ft_strncmp(d_name, cmp, ft_strlen(cmp))))
			{
				list = names_list(f_d);
			}
			return (list);
		}
	}
	else
	{
		if ((!ft_strcmp("", cmp) || !ft_strncmp(d_name, cmp, ft_strlen(cmp)))
		&& d_name[0] != '.')
			list = names_list(f_d);
		return (list);
	}
	return (NULL);
}

void	free_file_dir(char **file_dir)
{
	if (*file_dir)
		ft_strdel(file_dir);
}

void	init_vars(t_l **files_dirs_list, char **file_dir, t_l **node)
{
	*files_dirs_list = NULL;
	*file_dir = NULL;
	*node = NULL;
}
