/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:35:31 by afaraji           #+#    #+#             */
/*   Updated: 2020/10/31 20:52:37 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int	is_valid_word(char *s)
{
	int	i;

	if (s[0] != '_' && !ft_isalpha(s[0]))
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != '_' && !ft_isalnum(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_file(char *file, t_list_token *node)
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

int	manage_cmd_list(t_cmdlist *cmdlist)
{
	t_cmdlist		*node;
	int				ret;

	node = cmdlist;
	ret = 0;
	while (node)
	{
		ret = execute(node->and_or, node->bg);
		node = node->next;
	}
	free_cmd_list(cmdlist);
	return (ret);
}

int	join_escape(t_list_token *token)
{
	t_list_token	*node;

	node = token;
	while (node)
	{
		if (node->type == ESCAPE)
		{
			node->type = WORD;
			node->data[0] = '\0';
		}
		node = node->next;
	}
	return (0);
}

int	main_parse(char *line)
{
	t_list_token	*tokens;
	t_cmdlist		*cmdlist;

	tokens = ft_tokenize(line);
	ft_strdel(&line);
	if (lexer(&tokens) || verify_tokens(tokens) || need_append(tokens))
	{
		free_tokens(tokens);
		return (100);
	}
	join_escape(tokens);
	join_words(tokens);
	here_doc(tokens);
	cmdlist = token_split_sep_op(tokens);
	free_tokens(tokens);
	if (!cmdlist || g_var.errno)
	{
		if (cmdlist)
			free_cmd_list(cmdlist);
		return (42);
	}
	return (manage_cmd_list(cmdlist));
}
