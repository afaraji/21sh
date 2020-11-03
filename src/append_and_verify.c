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

int				is_valid_word(char *s)
{
	int	i;

	if (s[0] != '_' && !ft_isalpha(s[0]))
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != '_' && !ft_isalnum(s[i]))
			return(0);
		i++;
	}
	return (1);
}

int				is_all_digits(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int			is_valid_file(char *file, t_list_token *node)
{
	if (!node || !file)
		return (1);
	if (node->type <= -20 && node->type >= -31)
	{
		if (is_all_digits(file))
		{
			return (0);
		}
	}
	return (1);
}

int		need_append(t_list_token *tokens)
{
	t_list_token	*node;
	t_list_token	*ttt;
	char			*toappend;
	char			*tmp;
	int				typ;

	node = tokens;
	while (node->next)
		node = node->next;
	while (node && node->type == SPACE)
		node = node->prec;
	typ = node->type;
	if (typ == PIP || typ == ESCAPE || ((typ == QUOTE || typ == DQUOTE) && node->is_ok == 0))
	{
		tmp = readline(typ);
		if (!ft_strcmp(tmp, "\030") || !ft_strcmp(tmp, "\033"))
			return (1);
		if (typ == QUOTE || typ == DQUOTE)
		{
			toappend = ft_strjoin(node->data, "\n");
			toappend = ft_strjoin(toappend, tmp);
			toappend = ft_strjoin(tokentoa(typ), toappend);
			ttt = ft_tokenize(toappend);
			if (ttt->next)
				ttt->next->prec = node;
			node->data = ttt->data;
			node->type = ttt->type;
			node->is_ok = ttt->is_ok;
			node->next = ttt->next;
		}
		else
		{
			toappend = tmp;
			node->next = ft_tokenize(toappend);
		}
		ft_strdel(&toappend);
		if (lexer(&tokens) || verify_tokens(tokens))
		{
			return (100);
		}
		return (need_append(tokens));
	}
	return (0);
}

