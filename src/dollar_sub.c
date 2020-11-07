/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:57:42 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 18:58:01 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int		is_dollar(char *s)
{
	int i;

	if (!s)
		return (-42);
	i = 0;
	while (s[i] && (s[i] != '$' || (i > 0 && s[i - 1] == '\\')))
		i++;
	if (s[i] == '$')
		return (i);
	return (-42);
}

int		end_dollar_word(char *s, int start)
{
	int i;
	int bracket;

	bracket = 0;
	if (s[start + 1] == '{')
		bracket = 1;
	i = start + bracket + 1;
	if (s[i] == '!' || s[i] == '#' || s[i] == '$' || s[i] == '?')
		return (i + 1 + bracket);
	if (s[i] != '_' && !ft_isalpha(s[i]))
	{
		if (!bracket)
			return (i);
		return (-1);
	}
	while (s[i] && (s[i] == '_' || ft_isalnum(s[i])))
		i++;
	if (bracket)
	{
		if (s[i] == '}')
			return (i + 1);
		else
			return (-1);
	}
	return (i);
}

char	*get_dollar_var(char *s, int start, int end)
{
	char	*tmp;
	char	*var;
	int		index;
	int		len;

	if (start == end - 1)
		return (ft_strdup("$"));
	index = start + 1;
	len = end - start - 1;
	if (s[index] == '{' && s[index + len - 1] == '}')
	{
		index++;
		len -= 2;
	}
	tmp = ft_strsub(s, index, len);
	var = fetch_variables(tmp, -1);
	ft_strdel(&tmp);
	if (!var)
		return (ft_strdup(""));
	return (var);
}

char	*str_dollar_sub(char *str)
{
	int		start;
	int		end;
	char	*prefix;
	char	*suffix;
	char	*var;

	start = is_dollar(str);
	end = end_dollar_word(str, start);
	if (start < 0 || end < 0)
		return (str);
	prefix = ft_strsub(str, 0, start);
	var = get_dollar_var(str, start, end);
	suffix = ft_strjoin(var, &(str[end]));
	ft_strdel(&str);
	str = ft_strjoin(prefix, suffix);
	ft_strdel(&prefix);
	ft_strdel(&var);
	ft_strdel(&suffix);
	if (is_dollar(str) >= 0 && (end - start) > 1)
		str = str_dollar_sub(str);
	return (str);
}

int		dollar_sub(t_list_token **cmd_token)
{
	t_list_token	*node;

	node = *cmd_token;
	while (node)
	{
		if (node->type == WORD && is_dollar(node->data) >= 0)
		{
			node->data = str_dollar_sub(node->data);
		}
		node = node->next;
	}
	return (0);
}
