/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:41:39 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 17:42:31 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

t_list_token	*list_sub(t_list_token *start, t_list_token *end)
{
	t_list_token *head;
	t_list_token *node;

	if (!start)
		return (NULL);
	head = NULL;
	while (start)
	{
		if (!head)
		{
			node = (t_list_token *)malloc(sizeof(t_list_token));
			node->prec = NULL;
			head = node;
		}
		else
		{
			node->next = (t_list_token *)malloc(sizeof(t_list_token));
			node->next->prec = node;
			node = node->next;
		}
		if (start->data)
			node->data = ft_strdup(start->data);
		else
			node->data = NULL;
		node->is_ok = start->is_ok;
		node->type = start->type;
		node->next = NULL;
		if (start == end)
			break ;
		start = start->next;
	}
	return (head);
}

void			free_token_node(t_list_token **todel)
{
	ft_strdel(&((*todel)->data));
	free(*todel);
	*todel = NULL;
}

void			join_nodes(t_list_token *dst, t_list_token *todel)
{
	t_list_token	*node;
	char			*tmp;

	tmp = ft_strjoin(dst->data, todel->data);
	ft_strdel(&(dst->data));
	dst->data = tmp;
	dst->type = WORD;
	dst->next = todel->next;
	if (todel->next)
		todel->next->prec = dst;
	free_token_node(&todel);
}

void			join_words(t_list_token *token)
{
	t_list_token	*node;
	t_list_token	*tmp;

	node = token;
	while (node->next)
	{
		if (node->type == WORD || node->type == QUOTE || node->type == DQUOTE)
		{
			tmp = node->next;
			if (tmp->type == WORD || tmp->type == QUOTE || tmp->type == DQUOTE)
			{
				join_nodes(node, tmp);
				node = token;
			}
		}
		if (!(node->next))
			break ;
		node = node->next;
	}
}
