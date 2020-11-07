/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 23:14:10 by afaraji           #+#    #+#             */
/*   Updated: 2020/02/11 23:14:15 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

char	*delete_escape(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && (str[i + 1] == '$' || str[i + 1] == '"'))
		{
			str[i] = '\0';
			tmp = ft_strjoin(str, &str[i + 1]);
			ft_strdel(&str);
			str = tmp;
		}
		i++;
	}
	return (str);
}

char	*fetch_variables(char *key, int typ)
{
	t_variable	*node;

	node = g_var.var;
	while (node)
	{
		if ((node->env == typ || typ < 0) && !ft_strcmp(key, node->key))
			return (ft_strdup(node->value));
		node = node->next;
	}
	return (NULL);
}

int		is_assword(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		return (i + 1);
	}
	return (0);
}

int		lexer(t_list_token **cmd_token)
{
	if (!cmd_token || !(*cmd_token))
		return (1);
	if (keywords_alias_sub(cmd_token))
	{
		g_var.exit_status = 42;
		return (42);
	}
	tilde_sub(cmd_token);
	dollar_sub(cmd_token);
	return (0);
}
