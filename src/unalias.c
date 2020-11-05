/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 17:46:11 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/05 17:46:12 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

void	unset_alias_node(t_alias *prec, t_alias *node)
{
	if (prec == NULL)
	{
		g_var.aliases = node->next;
	}
	else
	{
		prec->next = node->next;
	}
	ft_strdel(&(node->key));
	ft_strdel(&(node->sub));
	free(node);
	node = NULL;
}

int		unset_alias(char *key)
{
	t_alias	*node;
	t_alias	*prec;

	if (g_var.aliases)
	{
		node = g_var.aliases;
		prec = NULL;
		while (node)
		{
			if (!ft_strcmp(key, node->key))
			{
				unset_alias_node(prec, node);
				return (0);
			}
			prec = node;
			node = node->next;
		}
	}
	ft_print(STDERR, "shell: unalias: %s: not found.\n", key);
	return (1);
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
		if (g_var.aliases)
			free_aliases(&g_var.aliases);
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
