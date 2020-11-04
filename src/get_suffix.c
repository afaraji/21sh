/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_suffix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:35:19 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 17:35:24 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

t_variable		*ass_word(t_list_token **cmd, t_list_token **end)
{
	t_variable	*var;
	int			i;

	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	if (*cmd && (*cmd)->type == WORD)
	{
		i = 1;
		while ((*cmd)->data[i])
		{
			if ((*cmd)->data[i] == '=')
				break ;
			i++;
		}
		if (i >= ft_strlen((*cmd)->data))
			return (NULL);
		var = (t_variable *)malloc(sizeof(t_variable));
		var->key = ft_strsub((*cmd)->data, 0, i);
		if (!is_valid_word(var->key))
		{
			ft_strdel(&(var->key));
			free(var);
			var = NULL;
			return (NULL);
		}
		var->value = ft_strdup(&((*cmd)->data[i + 1]));
		var->env = 1;
		*cmd = (*cmd)->next;
		return (var);
	}
	return (NULL);
}

t_cmd_prefix	*cmd_prefix(t_list_token **cmd, t_list_token **end)
{
	t_cmd_prefix	*node;

	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	node = (t_cmd_prefix *)malloc(sizeof(t_cmd_prefix));
	node->io_redirect = io_redirect(cmd, end);
	if (node->io_redirect)
	{
		node->ass_word = NULL;
		node->prefix = cmd_prefix(cmd, end);
		return (node);
	}
	node->ass_word = ass_word(cmd, end);
	if (node->ass_word)
	{
		node->io_redirect = NULL;
		node->prefix = cmd_prefix(cmd, end);
		return (node);
	}
	free(node);
	return (NULL);
}

char			*cmd_word(t_list_token **cmd, t_list_token **end)
{
	char	*word;

	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	if (((*cmd)->type == WORD || (*cmd)->type == QUOTE ||
														(*cmd)->type == DQUOTE))
	{
		word = ft_strdup((*cmd)->data);
		*cmd = (*cmd)->next;
		return (word);
	}
	return (NULL);
}

t_cmd_suffix	*cmd_suffix(t_list_token **cmd, t_list_token **end)
{
	t_cmd_suffix	*node;

	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	node = (t_cmd_suffix *)malloc(sizeof(t_cmd_suffix));
	node->suffix = NULL;
	node->io_redirect = io_redirect(cmd, end);
	if (node->io_redirect)
	{
		node->word = NULL;
		node->suffix = cmd_suffix(cmd, end);
		return (node);
	}
	node->word = cmd_word(cmd, end);
	if (node->word)
	{
		node->io_redirect = NULL;
		node->suffix = cmd_suffix(cmd, end);
		return (node);
	}
	free_suffix(node);
	return (NULL);
}
