/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:52:19 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/01 17:52:20 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int		file_or_dir_link(char **file)
{
	DIR			*dir;

	if ((dir = opendir(*file)) != NULL)
	{
		closedir(dir);
		ft_strdel(file);
		return (1);
	}
	else
	{
		ft_strdel(file);
		return (2);
	}
	return (0);
}

int		verify_type_1(char **file, struct stat st)
{
	if (S_ISDIR(st.st_mode))
	{
		ft_strdel(file);
		return (1);
	}
	if (S_ISLNK(st.st_mode))
	{
		if (file_or_dir_link(file) == 1)
			return (3);
		else if (file_or_dir_link(file) == 2)
			return (2);
	}
	else
	{
		ft_strdel(file);
		return (2);
	}
	return (0);
}

int		verify_type(char *str)
{
	struct stat	st;
	char		*file;

	file = ft_strdup(str);
	if (file[ft_strlen(file) - 1] == '/' && ft_strlen(file) - 1 > 0)
		file[ft_strlen(file) - 1] = '\0';
	if (lstat(file, &st) == 0)
	{
		if (verify_type_1(&file, st) == 1)
			return (1);
		else if (verify_type_1(&file, st) == 2)
			return (2);
		else if (verify_type_1(&file, st) == 3)
			return (3);
	}
	ft_strdel(&file);
	return (-1);
}
