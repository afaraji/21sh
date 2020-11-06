/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_1.c                                  :+:      :+:    :+:   */
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

char			**completion_split_1(char **table)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (table[i])
		i++;
	if (!(tmp = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = 0;
	while (table[i])
	{
		tmp[i] = ft_strdup(table[i]);
		i++;
	}
	free_tab(table);
	tmp[i] = ft_strdup("");
	tmp[i + 1] = NULL;
	return (tmp);
}

int				is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (2);
		i++;
	}
	return (0);
}

char			**completion_split(char *line)
{
	char	**table;

	table = NULL;
	if (!ft_strcmp(line, ""))
	{
		if (!(table = (char **)malloc(sizeof(char *) * 2)))
			return (NULL);
		table[0] = ft_strdup("");
		table[1] = NULL;
		return (table);
	}
	table = ft_strsplit(line, ' ');
	if (line[ft_strlen(line) - 1] == ' ')
	{
		return (completion_split_1(table));
	}
	return (table);
}

char			*completed_line(char *line, char *str)
{
	int		i;
	char	*left;
	char	*tmp;

	i = ft_strlen(line) - 1;
	while (i >= 0)
	{
		if (line[i] == '/' || line[i] == ' ')
			break ;
		i--;
	}
	left = ft_strsub(line, 0, i + 1);
	tmp = ft_strjoin(left, str);
	ft_strdel(&left);
	ft_strdel(&line);
	return (tmp);
}

int				get_home_path(char **str)
{
	t_variable	*var;
	char		*tmp;

	var = g_var.var;
	tmp = NULL;
	while (var)
	{
		if (!ft_strcmp(var->key, "HOME"))
		{
			tmp = ft_strsub(*str, 1, ft_strlen(*str));
			ft_strdel(str);
			*str = ft_strjoin(var->value, tmp);
			ft_strdel(&tmp);
			return (1);
		}
		var = var->next;
	}
	return (0);
}
