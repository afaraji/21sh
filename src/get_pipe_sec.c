/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe_sec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:37:02 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 17:37:30 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

char			*cmd_name(t_list_token **cmd, t_list_token **end)
{
	char	*name;

	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	if (((*cmd)->type == WORD || (*cmd)->type == QUOTE ||
		(*cmd)->type == DQUOTE))
	{
		name = ft_strdup((*cmd)->data);
		*cmd = (*cmd)->next;
		return (name);
	}
	return (NULL);
}

t_simple_cmd	*malloc_simple_cmd(void)
{
	t_simple_cmd	*ret;

	ret = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (!ret)
		return (NULL);
	ret->name = NULL;
	ret->word = NULL;
	ret->suffix = NULL;
	ret->prefix = NULL;
	return (ret);
}

t_simple_cmd	*get_simple_cmd(t_list_token *start, t_list_token *end)
{
	t_simple_cmd *ret;

	if (g_var.errno)
		return (NULL);
	ret = malloc_simple_cmd();
	ret->prefix = cmd_prefix(&start, &end);
	if (!g_var.errno && ret->prefix)
	{
		ret->word = cmd_word(&start, &end);
		if (ret->word)
		{
			ret->suffix = cmd_suffix(&start, &end);
			return (ret);
		}
		return (ret);
	}
	else if (!g_var.errno && (ret->name = cmd_name(&start, &end)))
	{
		ret->suffix = cmd_suffix(&start, &end);
		return (ret);
	}
	else if (!g_var.errno)
		g_var.errno = 122;
	free(ret);
	return (NULL);
}

t_pipe_seq		*ast_fill(t_list_token *tokens, t_list_token *node, int right)
{
	t_pipe_seq		*tmp;

	if (g_var.errno)
		return (NULL);
	tmp = (t_pipe_seq *)malloc(sizeof(t_pipe_seq));
	if (!tmp || g_var.errno)
		return (NULL);
	tmp->left = get_simple_cmd(tokens, node);
	if (right && !g_var.errno)
		tmp->right = ast(node->next);
	else
		tmp->right = NULL;
	if (g_var.errno)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

t_pipe_seq		*ast(t_list_token *tokens)
{
	t_list_token	*node;
	t_list_token	*prec;

	if (!tokens || g_var.errno)
	{
		if (!g_var.errno)
			g_var.errno = 122;
		ft_print(STDERR, "syntax error, unexpected token.\n");
		return (NULL);
	}
	node = tokens;
	while (node)
	{
		if (node->type == PIP)
			return (ast_fill(tokens, node, 1));
		prec = node;
		node = node->next;
	}
	return (ast_fill(tokens, prec, 0));
}
