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

t_simple_cmd	*get_simple_cmd(t_list_token *start, t_list_token *end)
{
	t_simple_cmd *ret;

	if (g_var.errno)
		return (NULL);
	ret = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	ret->name = NULL;
	ret->word = NULL;
	ret->suffix = NULL;
	ret->prefix = cmd_prefix(&start, &end);
	if (ret->prefix)
	{
		ret->word = cmd_word(&start, &end);
		if (ret->word)
		{
			ret->suffix = cmd_suffix(&start, &end);
			return (ret);
		}
		return (ret);
	}
	else if ((ret->name = cmd_name(&start, &end)))
	{
		ret->suffix = cmd_suffix(&start, &end);
		return (ret);
	}
	else
	{
		if (!g_var.errno)
		{
			ft_putstr_fd("syntax error, unexpected token near '", 2);
			ft_putstr_fd(tokentoa(start->type), 2);
			ft_putstr_fd("'\n", 2);
			g_var.errno = 122;
		}
		return (NULL);
	}
}

t_pipe_seq		*ast(t_list_token *tokens)
{
	t_list_token	*node;
	t_list_token	*prec;
	t_pipe_seq		*tmp;

	if (!tokens || g_var.errno)
	{
		if (!g_var.errno)
		{
			ft_putstr_fd("syntax error, unexpected <newline>\n", 2);
			g_var.errno = 122;
		}
		return (NULL);
	}
	node = tokens;
	tmp = NULL;
	while (node)
	{
		if (node->type == PIP)
		{
			tmp = (t_pipe_seq *)malloc(sizeof(t_pipe_seq));
			tmp->left = get_simple_cmd(tokens, node);
			tmp->right = ast(node->next);
			return (tmp);
		}
		prec = node;
		node = node->next;
	}
	tmp = (t_pipe_seq *)malloc(sizeof(t_pipe_seq));
	tmp->left = get_simple_cmd(tokens, prec);
	tmp->right = NULL;
	return (tmp);
}
