/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:37:57 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 18:39:19 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

char	*ft_strsub_delimit(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	return (ft_strsub(s, 0, i));
}

int		alias_infinit_loop(char *str, t_alias *aliases)
{
	char	*tmp;
	t_alias	*node;

	node = aliases;
	tmp = ft_strdup(str);
	while (node)
	{
		if (!ft_strcmp(tmp, node->key))
		{
			ft_strdel(&tmp);
			tmp = ft_strsub_delimit(node->sub, ' ');
			if (!ft_strcmp(tmp, str))
			{
				ft_strdel(&tmp);
				return (1);
			}
			else
				node = aliases;
		}
		node = node->next;
	}
	return (0);
}

int		alias_sub(t_list_token *word, t_alias *aliases)
{
	t_alias	*node;

	node = aliases;
	while (node)
	{
		if (!ft_strcmp(word->data, node->key))
		{
			if (!alias_infinit_loop(node->key, aliases))
			{
				ft_strdel(&(word->data));
				word->data = ft_strdup(node->sub);
				return (1);
			}
		}
		node = node->next;
	}
	return (0);
}

void	insert_alias(char *key, char *sub)
{
	t_alias		*node;

	if (g_var.aliases)
	{
		node = g_var.aliases;
		while (node->next)
			node = node->next;
		node->next = (t_alias *)malloc(sizeof(t_alias));
		node->next->next = NULL;
		node->next->key = ft_strdup(key);
		node->next->sub = ft_strdup(sub);
	}
	else
	{
		g_var.aliases = (t_alias *)malloc(sizeof(t_alias));
		g_var.aliases->next = NULL;
		g_var.aliases->key = ft_strdup(key);
		g_var.aliases->sub = ft_strdup(sub);
	}
}

void	get_aliases(void)
{
	insert_alias("toto", "lala qwerty");
	insert_alias("lala", "yoyo");
	insert_alias("yoyo", "test alias");
	insert_alias("abc", "abce lol  123");
}
