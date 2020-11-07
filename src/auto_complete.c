/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
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

char			**auto_completion_3(char **splited_line, int i)
{
	if (splited_line[i][1] == '{')
	{
		return (var_search(splited_line[i] + 2));
	}
	else
		return (var_search(splited_line[i] + 1));
}

char			**auto_completion_1(t_line *line)
{
	char	**result;
	char	**splited_line;
	int		i;

	splited_line = completion_split(line->str);
	result = NULL;
	i = 0;
	while (splited_line[i + 1])
		i++;
	if (splited_line[i][0] == '~' && splited_line[i][1] == '/')
		get_home_path(&splited_line[i]);
	if (splited_line[i][0] == '$')
	{
		result = auto_completion_3(splited_line, i);
	}
	else if (i == 0 && splited_line[0][0] == '.')
		result = files_dirs_search(splited_line[0]);
	else if (i != 0 || is_path(splited_line[i]) != 0)
		result = files_dirs_search(splited_line[i]);
	else
		result = cmd_search(splited_line[0]);
	if (splited_line)
		free_tab(splited_line);
	return (result);
}

int				auto_completion_2(char **result, t_line *line)
{
	ft_putchar('\n');
	print_result(result, line);
	free_tab(result);
	return (2);
}

int				is_valid_tab(char **t)
{
	if (!t)
		return (0);
	if (t[0] == NULL)
	{
		free_tab(t);
		return (0);
	}
	return (1);
}

int				auto_completion(t_line *line)
{
	char	**result;
	int		j;

	result = auto_completion_1(line);
	if (!is_valid_tab(result))
	{
		return (0);
	}
	j = 0;
	while (result && result[j + 1])
		j++;
	if (j == 0)
	{
		line->str = completed_line(line->str, result[0]);
		free_tab(result);
		if (line->init_pos == line->row)
			display_line_from_begin(line);
		else
			display_line(line);
		move_curs_right(line);
		return (1);
	}
	else
		return (auto_completion_2(result, line));
	return (0);
}
