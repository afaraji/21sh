/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserved_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:55:01 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 18:55:19 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int		is_reserved(char *str)
{
	char	**rsrved;
	int		i;

	i = 0;
	rsrved = ft_strsplit(RSRVDWORD, '|');
	while (rsrved[i])
	{
		if (ft_strcmp(str, rsrved[i]) == 0)
		{
			free_tab(rsrved);
			return (1);
		}
		i++;
	}
	free_tab(rsrved);
	return (0);
}

void	parse_and_replace(t_list_token **cmd_token, t_list_token *node)
{
	t_list_token	*toinsert;
	t_list_token	*tmp;

	toinsert = ft_tokenize(node->data);
	tmp = toinsert;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node->next;
	if (node->next)
		node->next->prec = tmp;
	if (node->prec)
	{
		tmp = node->prec;
		toinsert->prec = tmp;
		tmp->next = toinsert;
	}
	else
	{
		*cmd_token = toinsert;
	}
	ft_strdel(&(node->data));
	free(node);
}

int		ft_or(int m, int a, int b, int c)
{
	return ((m == a || m == b || m == c) ? 1 : 0);
}

int		keywords_alias_sub_2(t_list_token **cmd_token, t_list_token *node)
{
	parse_and_replace(cmd_token, node);
	if (keywords_alias_sub(cmd_token))
		return (1);
	return (0);
}

int		keywords_alias_sub(t_list_token **cmd_token)
{
	t_list_token	*node;

	node = *cmd_token;
	while (node)
	{
		if (ft_or(node->type, SMCLN, ANDLG, ORLG) ||
						ft_or(node->type, PIP, BGJOB, 0) || node == *cmd_token)
		{
			if (node != *cmd_token)
				node = node->next;
			while (node && node->type == SPACE)
				node = node->next;
			if (node && node->type == WORD && is_reserved(node->data))
			{
				ft_print(STDERR, "found [%s] not implimented.\n", node->data);
				return (1);
			}
			else if (node && node->type == WORD)
				if (alias_sub(node, g_var.aliases))
					return (keywords_alias_sub_2(cmd_token, node));
		}
		if (node)
			node = node->next;
	}
	return (0);
}
