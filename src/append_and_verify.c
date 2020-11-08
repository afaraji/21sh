/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_and_verify.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:47:03 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 17:47:23 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int		is_all_digits(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int		is_need_append(t_list_token *node)
{
	int typ;

	typ = node->type;
	if (typ == PIP || typ == ESCAPE)
		return (1);
	if ((typ == QUOTE || typ == DQUOTE) && node->is_ok == 0)
		return (1);
	return (0);
}

char	*read_to_append(t_list_token *node)
{
	char	*str;

	str = readline(node->type);
	if (!ft_strcmp(str, "\030") || !ft_strcmp(str, "\033"))
	{
		ft_strdel(&str);
		return (NULL);
	}
	return (str);
}

void	replace_node(t_list_token **dst, t_list_token **src)
{
	if ((*src)->next)
		(*src)->next->prec = *dst;
	ft_strdel(&((*dst)->data));
	(*dst)->data = ft_strdup((*src)->data);
	(*dst)->type = (*src)->type;
	(*dst)->is_ok = (*src)->is_ok;
	(*dst)->next = (*src)->next;
	ft_strdel(&((*src)->data));
	free((*src));
}

int		need_append(t_list_token *tokens)
{
	t_list_token	*node;
	t_list_token	*ttt;
	char			*toappend;
	char			*tmp;

	node = get_last_node_toappend(tokens);
	if (is_need_append(node))
	{
		if (!(tmp = read_to_append(node)))
			return (1);
		if (node->type == QUOTE || node->type == DQUOTE)
		{
			toappend = ft_4strjoin(tokentoa(node->type), node->data, "\n", tmp);
			ttt = ft_tokenize(toappend);
			replace_node(&node, &ttt);
			ft_strdel(&toappend);
		}
		else
			node->next = ft_tokenize(tmp);
		ft_strdel(&tmp);
		if (lexer(&tokens) || verify_tokens(tokens))
			return (100);
		return (need_append(tokens));
	}
	return (0);
}
