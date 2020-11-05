/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 18:37:57 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/04 22:39:19 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

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

void	print_alias(t_alias *alias)
{
	t_alias	*node;

	if (!alias)
		return ;
	node = alias;
	while (node)
	{
		ft_print(STDOUT, "alias %s='%s'\n", node->key, node->sub);
		node = node->next;
	}
}

int		alias_findandprint(char *str)
{
	t_alias	*node;

	if (g_var.aliases)
	{
		node = g_var.aliases;
		while (node)
		{
			if (!ft_strcmp(str, node->key))
			{
				ft_print(STDOUT, "alias %s='%s'\n", node->key, node->sub);
				return (0);
			}
			node = node->next;
		}
	}
	ft_print(STDERR, "shell: alias: %s: not found.\n", str);
	return (1);
}

int		alias_insert(char *str)
{
	int		i;
	t_alias	*node;
	char	*key;

	i = is_assword(str);
	key = ft_strsub(str, 0, i - 1);
	if (g_var.aliases)
	{
		node = g_var.aliases;
		while (node)
		{
			if (!ft_strcmp(key, node->key))
			{
				ft_strdel(&key);
				ft_strdel(&(node->sub));
				node->sub = ft_strdup(&str[i]);
				return (0);
			}
			node = node->next;
		}
	}
	insert_alias(key, &str[i]);
	ft_strdel(&key);
	return (0);
}

int		ft_alias(char **av)
{
	int i;
	int ret;

	ret = 0;
	if (!av[1])
	{
		print_alias(g_var.aliases);
	}
	else
	{
		i = 1;
		while (av[i])
		{
			if (is_assword(av[i]) > 1)
				ret = (alias_insert(av[i]) ? 1 : ret);
			else
				ret = (alias_findandprint(av[i]) ? 1 : ret);
			i++;
		}
	}
	return (ret);
}
