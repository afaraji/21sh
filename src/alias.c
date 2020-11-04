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
	insert_alias("lla", "ls -la");
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
				ft_strdel(&(node->sub));
				node->sub = ft_strdup(&str[i]);
				break;
			}
			node = node->next;
		}
	}
	else
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
			if (is_assword(av[i]))
				ret = (alias_insert(av[i]) ? 1 : ret);
			else
				ret = (alias_findandprint(av[i]) ? 1 : ret);
			i++;
		}
	}
	return (ret);
}

int		unset_alias(char *key)
{
	//look for key in alias_list
	//if found delet node
	//else print error and return 1
	return (0);
}

int		ft_unalias(char **av)
{
	int	i;
	int ret;

	if (!av[1])
	{
		ft_print(STDERR, "unalias: usage: unalias [-a] name [name ...]\n");
		return (2);
	}
	if (!ft_strcmp(av[1], "-a"))
	{
		free_aliases(g_var.aliases);
		return (0);
	}
	else
	{
		i = 1;
		ret = 0;
		while (av[i])
		{
			ret = (unset_alias(av[i]) ? 1 : ret);
			i++;
		}
	}
	return (ret);
}
