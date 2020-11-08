/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_splited_and_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:45:43 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 17:46:05 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

t_and_or	*tkn_andor(t_list_token *tmp, t_list_token **start, t_and_or *list)
{
	t_and_or	*node;

	if (!list)
	{
		node = get_andor_list(*start, 0, tmp->prec);
		*start = tmp;
		return (node);
	}
	node = list;
	while (node->next)
		node = node->next;
	node->next = get_andor_list((*start)->next, (*start)->type, tmp->prec);
	*start = tmp;
	return (list);
}

t_and_or	*token_split_andor(t_list_token *start, t_list_token *end)
{
	t_and_or		*list;
	t_and_or		*node;
	t_list_token	*tmp;

	if (!start || g_var.errno)
		return (NULL);
	tmp = start;
	list = NULL;
	while (tmp && tmp != end)
	{
		if (tmp->type == ORLG || tmp->type == ANDLG)
			list = tkn_andor(tmp, &start, list);
		tmp = tmp->next;
	}
	if (!list)
		list = get_andor_list(start, 0, end);
	else
	{
		node = list;
		while (node->next)
			node = node->next;
		node->next = get_andor_list(start->next, start->type, end);
	}
	return (list);
}

t_cmdlist	*sep_op_mllc(t_list_token *tokens, t_list_token *tmp, int bg)
{
	t_cmdlist	*node;

	node = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	if (!node)
		return (NULL);
	node->and_or = token_split_andor(tokens, tmp);
	if (node->and_or == NULL || g_var.errno)
	{
		free(node);
		return (NULL);
	}
	node->bg = (bg == BGJOB) ? 1 : 0;
	node->next = NULL;
	return (node);
}

t_cmdlist	*token_split_sep_op_2(t_list_token **tokens)
{
	t_cmdlist		*list;
	t_cmdlist		*node;
	t_list_token	*tmp;

	tmp = *tokens;
	list = NULL;
	while (tmp)
	{
		if (tmp->type == SMCLN || tmp->type == BGJOB)
		{
			if (!list)
			{
				node = sep_op_mllc(*tokens, tmp->prec, tmp->type);
				list = node;
			}
			else
			{
				node->next = sep_op_mllc((*tokens)->next, tmp->prec, tmp->type);
				node = node->next;
			}
			*tokens = tmp;
		}
		tmp = tmp->next;
	}
	return (list);
}

t_cmdlist	*token_split_sep_op(t_list_token *tokens)
{
	t_cmdlist		*list;
	t_cmdlist		*node;
	t_list_token	*tmp;

	if (!tokens || g_var.errno)
		return (NULL);
	tmp = tokens;
	list = token_split_sep_op_2(&tokens);
	if (!list)
		list = sep_op_mllc(tokens, NULL, 0);
	else if (tokens->next)
	{
		node = list;
		while (node->next)
			node = node->next;
		node->next = sep_op_mllc(tokens->next, NULL, 0);
	}
	return (list);
}
