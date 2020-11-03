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

t_and_or	*get_andor_list(t_list_token *strt, int dep, t_list_token *end)
{
	t_and_or		*node;
	t_list_token	*tmp;

	if (!strt)
		return (NULL);
	if (!(node = (t_and_or *)malloc(sizeof(t_and_or))))
		return (NULL);
	node->next = NULL;
	tmp = list_sub(strt, end);
	node->ast = ast(tmp);
	free_tokens(tmp);
	if (!(node->ast))
		return (NULL);
	node->dependent = 0;
	if (dep == ANDLG)
		node->dependent = 1;
	if (dep == ORLG)
		node->dependent = 2;
	return (node);
}

t_and_or	*token_split_andor(t_list_token *start, t_list_token *end, int bg)
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
		{
			if (!list)
			{
				node = get_andor_list(start, 0, tmp->prec);
				list = node;
			}
			else
			{
				node->next = get_andor_list(start->next, start->type, tmp->prec);
				node = node->next;
			}
			start = tmp;
		}
		tmp = tmp->next;
	}
	if (!list)
	{
		list = get_andor_list(start, 0, end);
	}
	else
	{
		node->next = get_andor_list(start->next, start->type, end);
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
	list = NULL;
	while (tmp)
	{
		if (tmp->type == SMCLN || tmp->type ==BGJOB)
		{
			if (!list)
			{
				node = (t_cmdlist *)malloc(sizeof(t_cmdlist));
				node->and_or = token_split_andor(tokens, tmp->prec, tmp->type);
				list = node;
			}
			else
			{
				node->next = (t_cmdlist *)malloc(sizeof(t_cmdlist));
				node = node->next;
				node->and_or = token_split_andor(tokens->next, tmp->prec, tmp->type);
			}
			(tmp->type == BGJOB) ? (node->bg = 1) : (node->bg = 0);
			tokens = tmp;
			node->next = NULL;
		}
		tmp = tmp->next;
	}
	if (!list)
	{
		list = (t_cmdlist *)malloc(sizeof(t_cmdlist));
		list->and_or = token_split_andor(tokens, NULL, SMCLN);
		list->bg = 0;
		list->next = NULL;
	}
	else if (tokens->next)
	{

		node->next = (t_cmdlist *)malloc(sizeof(t_cmdlist));
		node = node->next;
		node->and_or = token_split_andor(tokens->next, NULL, SMCLN);
		node->bg = 0;
		node->next = NULL;
	}
	return (list);
}

