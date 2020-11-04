/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_d_completion_3.c                                 :+:      :+:    :+:   */
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

char			*get_path_2(char **str, int i)
{
	char	*tmp1;
	char	*tmp2;

	tmp2 = NULL;
	tmp1 = ft_strsub(*str, 0, i + 1);
	if (tmp1[0] == '/' || (tmp1[0] == '.' && tmp1[1] == '/'))
	{
		return (tmp1);
	}
	else
	{
		tmp2 = ft_strjoin("./", tmp1);
		ft_strdel(&tmp1);
		return (tmp2);
	}
}

int				get_path_1(char *str)
{
	int		index;

	index = ft_strlen(str) - 1;
	while (index >= 0)
	{
		if (str[index] == '/')
			break ;
		index--;
	}
	return (index);
}

char			*get_path(char *str)
{
	int		i;

	i = get_path_1(str);
	if (i == -1)
	{
		if (!ft_strcmp(str, ""))
		{
			return (ft_strdup("./"));
		}
	}
	else if (i != -1)
		return (get_path_2(&str, i));
	return (ft_strdup(str));
}

char			*get_to_cmp(char *str)
{
	int		i;
	int		j;
	char	*file_to_find;

	i = 0;
	j = 0;
	file_to_find = NULL;
	if (str == NULL)
		return (ft_strdup(""));
	while (str[i] != '\0')
	{
		if (str[i] == '/')
			j = i + 1;
		i++;
	}
	if (i == 1)
		return (ft_strdup(""));
	file_to_find = ft_strsub(str, j, i);
	return (file_to_find);
}
