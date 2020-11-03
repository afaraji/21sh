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

char		*here_doc_string(char *word)
{
	char	*str;
	char	*tmp;
	char	*buff;

	str = ft_strdup("");
	while (1)
	{
		buff = readline(SMLSML);
		if (!ft_strcmp(buff, "\033"))
		{
			g_var.errno = 1;
			ft_strdel(&buff);
			ft_strdel(&str);
			return (ft_strdup(""));
		}
		if (!ft_strcmp(buff, "\030"))
		{
			ft_strdel(&buff);
			return (str);
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
	while (node)
	{
		if (node->type == SMLSML)
		{
			while (node->next && node->next->type == SPACE)
				node = node->next;
			if (!node->next)
				return;
			if (node->next->type == WORD)
			{
				str = str_dollar_sub(here_doc_string(node->next->data));
			}
			else if (node->next->type == QUOTE|| node->next->type == DQUOTE)
			{
				str = here_doc_string(node->next->data);
			}
			ft_strdel(&(node->next->data));
			node->next->data = str;
			node->next->type = QUOTE;
			node->next->is_ok = 1;
		}
		node = node->next;
	}
}

