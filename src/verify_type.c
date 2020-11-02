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

#include "builtins.h"

int		verify_type(char *str)
{
	struct stat	st;
	DIR			*dir;
	char		*file;

	file = ft_strdup(str);
	if (file[ft_strlen(file) - 1] == '/' && ft_strlen(file) - 1 > 0)
		file[ft_strlen(file) - 1] = '\0';
	if (lstat(file, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (1);
		if (S_ISLNK(st.st_mode))
		{
			if ((dir = opendir(file)) != NULL)
			{
				closedir(dir);
				return (3);
			}
			else
				return (2);
		}
		else
			return (2);
	}
	return (-1);
}
