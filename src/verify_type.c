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

int		verify_type_link(char *file)
{
	DIR	*dir;

	if ((dir = opendir(file)) != NULL)
	{
		closedir(dir);
		return (3);
	}
	return (2);
}

int		verify_type(char *str)
{
	struct stat			st;
	int					ret;
	char				*file;

	file = ft_strdup(str);
	if (file[ft_strlen(file) - 1] == '/' && ft_strlen(file) - 1 > 0)
		file[ft_strlen(file) - 1] = '\0';
	ret = -1;
	if (lstat(file, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			ret = 1;
		else if (S_ISLNK(st.st_mode))
		{
			ret = verify_type_link(file);
		}
		else
			ret = 2;
	}
	ft_strdel(&file);
	return (ret);
}
