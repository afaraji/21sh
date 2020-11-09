/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:48:14 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 17:48:20 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

void	io_here_err(t_list_token **cmd, t_list_token **end)
{
	ft_putstr_fd("syntax error, unexpected token near '", 2);
	if (*cmd)
	{
		ft_putstr_fd(tokentoa((*cmd)->type), 2);
	}
	else
	{
		ft_putstr_fd(tokentoa((*end)->type), 2);
	}
	ft_putstr_fd("'\n", 2);
	g_var.errno = 121;
	*cmd = NULL;
}

char	*io_here(t_list_token **cmd, t_list_token **end, int *r_type)
{
	char	*file;

	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	if ((*cmd)->type == SMLSML)
	{
		*r_type = (*cmd)->type;
		*cmd = (*cmd)->next;
		while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
			*cmd = (*cmd)->next;
		if (*cmd && (ft_or((*cmd)->type, WORD, QUOTE, DQUOTE)))
		{
			if (is_valid_file((*cmd)->data, (*cmd)->next))
			{
				file = ft_strdup((*cmd)->data);
				*cmd = (*cmd)->next;
				return (file);
			}
			return (ft_strdup(""));
		}
		io_here_err(cmd, end);
	}
	return (NULL);
}

char	*here_doc_signal(char *buff, char *str)
{
	if (!ft_strcmp(buff, "\033"))
	{
		g_var.errno = 1;
		ft_strdel(&buff);
		ft_strdel(&str);
		return (ft_strdup(""));
	}
	else
	{
		ft_strdel(&buff);
		return (str);
	}
}

char	*here_doc_string(char *word)
{
	char	*str;
	char	*tmp;
	char	*buff;

	str = ft_strdup("");
	while (1)
	{
		buff = readline(SMLSML);
		if (!ft_strcmp(buff, "\033") || !ft_strcmp(buff, "\030"))
		{
			return (here_doc_signal(buff, str));
		}
		if (!ft_strcmp(buff, word))
		{
			ft_strdel(&buff);
			return (str);
		}
		tmp = ft_strjoin(str, buff);
		ft_strdel(&str);
		str = ft_strjoin(tmp, "\n");
		ft_strdel(&tmp);
		ft_strdel(&buff);
	}
	return (NULL);
}

void	here_doc(t_list_token *head)
{
	t_list_token	*node;
	char			*str;

	node = head;
	while (!g_var.errno && node)
	{
		if (node->type == SMLSML)
		{
			while (node->next && node->next->type == SPACE)
				node = node->next;
			if (!node->next)
				return ;
			if (node->next->type == WORD)
				str = str_dollar_sub(here_doc_string(node->next->data));
			else if (node->next->type == QUOTE || node->next->type == DQUOTE)
				str = here_doc_string(node->next->data);
			else
				return ;
			ft_strdel(&(node->next->data));
			node->next->data = str;
			node->next->type = QUOTE;
			node->next->is_ok = 1;
		}
		node = node->next;
	}
}
