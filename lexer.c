/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 23:14:10 by afaraji           #+#    #+#             */
/*   Updated: 2020/02/11 23:14:15 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int		alias_sub(t_list_token *word, t_alias *aliases)
{
	t_alias	*node;

	node = aliases;
	while (node)
	{
		if (ft_strcmp(word->data, node->sub))
			return (0);
		node = node->next;
	}
	node = aliases;
	while (node)
	{
		if (!ft_strcmp(word->data, node->key))
		{
			free(word->data);
			word->data = ft_strdup(node->sub);
			return (1);
		}
		node = node->next;
	}
	return(0);
}

int		is_reserved(char *str)
{
	char *rsrved[18] = {"!", "{", "}", "case", "do", "done", "elif", "else", "esac",
						"fi", "for", "if", "in", "then", "until", "while", ")", "("};
	int i;

	i = 0;
	while (i < 18)
	{
		if (ft_strcmp(str, rsrved[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

t_alias		*get_aliases(void)
{
	t_alias		*aliases;
	t_alias		*node;

	aliases = (t_alias *)malloc(sizeof(t_alias));
	aliases->key = ft_strdup("toto");
	aliases->sub = ft_strdup("echo hello world");
	aliases->next = (t_alias *)malloc(sizeof(t_alias));
	node = aliases->next;
	node->key = ft_strdup("tata");
	node->sub = ft_strdup("echo good night");
	node->next = (t_alias *)malloc(sizeof(t_alias));
	node = node->next;
	node->key = ft_strdup("lolo");
	node->sub = ft_strdup("echo balalalallalalalalalal");
	node->next = NULL;
	return (aliases);
}


int		lexer(t_list_token **cmd_token)
{
	t_list_token *node;

	node = *cmd_token;
	//give head to be treated.
	while (node)
	{
		if(_OR(node->type, SMCLN, ANDLG, ORLG, PIP, BGJOB) || node == *cmd_token)
		{
			while (node && node->type == SPACE)
				node = node->next;
			if (node && node->type == WORD && is_reserved(node->data))
			{
				printf("found '%s' - not implimented yet", node->data);
				return (1);
			}
			else if (node && node->type == WORD)
			{
				if (alias_sub(node, get_aliases()))
				{
					parse_and_eplace() // parse node->data and insert it and replace wit it node.
					lexer(cmd_token);
				}
			}
			
		}
		node = node->next;
	}
	return (0);
}