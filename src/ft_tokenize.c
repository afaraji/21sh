/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tokens_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:26:35 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 17:26:40 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

t_list_token	*add_word_int(int *index, char *str)
{
	int				i;
	t_list_token	*node;

	i = *index;
	while (str[i] && is_op(str, i) == 0)
	{
		i++;
	}
	node = (t_list_token *)malloc(sizeof(t_list_token));
	if (!node)
		return (NULL);
	node->type = WORD;
	node->data = ft_strsub(str, *index, i - *index);
	node->next = NULL;
	node->prec = NULL;
	*index = i;
	return (node);
}

t_list_token	*tokenize(char *str, int *i)
{
	int				op;

	op = is_op(str, *i);
	if (op < 0)
	{
		if (op == QUOTE)
			return (add_quote(i, str));
		else if (op == DQUOTE)
			return (add_dquote(i, str));
		else if (op == SPACE)
			return (add_space(i, str));
		else if (op == ESCAPE)
			return (add_escape(i, str));
		else
			return (add_op(i, op));
	}
	else
		return (add_word_int(i, str));
}

t_list_token	*ft_tokenize(char *str)
{
	t_list_token	*head;
	t_list_token	*node;
	int				i;

	head = NULL;
	i = 0;
	while (str[i])
	{
		if (!head)
		{
			head = tokenize(str, &i);
			head->prec = NULL;
			node = head;
		}
		else
		{
			node->next = tokenize(str, &i);
			node->next->prec = node;
			node = node->next;
		}
	}
	return (head);
}
