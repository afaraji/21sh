/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_assignement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:28:03 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 18:28:26 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

t_variable	*var_dup(t_variable *var)
{
	t_variable	*node;

	node = (t_variable *)malloc(sizeof(t_variable));
	if (!node)
		return (NULL);
	node->env = var->env;
	var->value = str_dollar_sub(var->value);
	node->value = ft_strdup(var->value);
	node->key = ft_strdup(var->key);
	node->next = NULL;
	return (node);
}

int			assignement_sub(t_variable *head, t_cmd_prefix *node)
{
	t_variable	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->env != 2 && !ft_strcmp(tmp->key, node->ass_word->key))
		{
			node->ass_word->value = str_dollar_sub(node->ass_word->value);
			tmp->env = node->ass_word->env;
			ft_strdel(&(tmp->value));
			tmp->value = ft_strdup(node->ass_word->value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int			do_assignement(t_cmd_prefix *pref, t_variable *head, int env)
{
	t_cmd_prefix	*node;
	t_variable		*tmp;

	node = pref;
	while (node)
	{
		if (node->ass_word)
		{
			node->ass_word->env = (node->ass_word->env == 2) ? 2 : env;
			if (!assignement_sub(head, node))
			{
				tmp = head;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = var_dup(node->ass_word);
			}
		}
		node = node->prefix;
	}
	return (0);
}
