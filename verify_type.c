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

#include "minishell.h"

int		verify_type(char *file)
{
	struct stat			st;
	int					ret;
	DIR					*dir;

	if ((ret = lstat(file, &st)) == 0)
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
	if (ret == -1)
		return (-1);
	return (0);
}