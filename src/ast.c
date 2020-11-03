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

int		manage_cmd_list(t_cmdlist *cmdlist)
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

int		main_parse(char *line)
{
	t_list_token	*tokens;
	t_cmdlist		*cmdlist;
	int				ret;

	tokens = ft_tokenize(line);
	g_var.errno = 0;
	if (lexer(&tokens) || verify_tokens(tokens))
	{
		return (100);
	}
	if (need_append(tokens))
		return (100);
	join_words(tokens);
	here_doc(tokens);
	cmdlist = token_split_sep_op(tokens);
	free_tokens(tokens);
	if (!cmdlist || g_var.errno)
		return (42);
	return (manage_cmd_list(cmdlist));
}
