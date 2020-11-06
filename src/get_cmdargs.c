/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdargs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:19:11 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 18:19:44 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

t_l		*fill_get_args(char *str)
{
	t_l	*node;

	node = (t_l *)malloc(sizeof(t_l));
	if (!node)
		return (NULL);
	node->data = ft_strdup(str);
	node->next = NULL;
	return (node);
}

t_l		*get_args(t_simple_cmd *cmd)
{
	t_l				*head;
	t_l				*node;
	t_cmd_suffix	*tmp;

	if (!(cmd->name) && !(cmd->word))
		return (NULL);
	if (!(head = (t_l *)malloc(sizeof(t_l))))
		return (NULL);
	if (cmd->name)
		head->data = ft_strdup(cmd->name);
	else
		head->data = ft_strdup(cmd->word);
	head->next = NULL;
	node = head;
	if (cmd->suffix)
	{
		tmp = cmd->suffix;
		while (tmp)
		{
			if (tmp->word && (node->next = fill_get_args(tmp->word)))
				node = node->next;
			tmp = tmp->suffix;
		}
	}
	return (head);
}

int		is_builtin(char *str)
{
	char	**b_in_list;
	int		i;

	b_in_list = ft_strsplit(BUILTINS, '|');
	if (!str || !ft_strcmp(str, ""))
	{
		free_tab(b_in_list);
		return (0);
	}
	i = 0;
	while (b_in_list[i])
	{
		if (!ft_strcmp(b_in_list[i], str))
		{
			free_tab(b_in_list);
			return (i + 1);
		}
		i++;
	}
	free_tab(b_in_list);
	return (0);
}

t_l		*var_sub(t_l *head)
{
	t_l		*node;
	t_l		*next_node;
	char	**t;
	int		i;

	next_node = head->next;
	head->data = str_dollar_sub(head->data);
	t = ft_strsplit(head->data, ' ');
	ft_strdel(&(head->data));
	i = 1;
	if (!t || !t[0])
	{
		head->data = ft_strdup("");
		return (head);
	}
	head->data = ft_strdup(t[0]);
	node = head;
	while (t[i])
	{
		node->next = fill_get_args(t[i]);
		node = node->next;
		i++;
	}
	node->next = next_node;
	return (head);
}

char	**get_arg_var_sub(t_simple_cmd *cmd)
{
	t_l	*list;

	list = get_args(cmd);
	return (list_to_tab(list));
}

/*
**	node = list;
**	while (node)
**	{
**		if (is_dollar(node->data) > -1)
**		{
**			node = var_sub(node);
**		}
**		node = node->next;
**	}
*/
