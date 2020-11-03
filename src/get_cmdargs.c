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

char	**list_to_tab(t_l *list)
{
	t_l		*node;
	int		i;
	char	**args;

	if (!list)
		return (NULL);
	node = list;
	i = 0;
	while (node)
	{
		if (ft_strcmp(node->data, ""))
			i++;
		node = node->next;
	}
	if (!(args = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	node = list;
	i = 0;
	while(node)
	{
		if (ft_strcmp(node->data, ""))
		{
			args[i] = ft_strdup(node->data);
			i++;
		}
		node = node->next;
	}
	args[i] = NULL;
	free_l(list);
	return (args);
}

t_l		*get_args(t_simple_cmd	*cmd)
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
			if (tmp->word)
			{
				node->next = (t_l *)malloc(sizeof(t_l));
				node->next->data = ft_strdup(tmp->word);
				node->next->next = NULL;
				node = node->next;
			}
			tmp = tmp->suffix;
		}
	}
	return (head);
}

int		is_builtin(char *str)
{
	char	*b_in_list[] = {"echo", "export", "cd", "setenv", "unsetenv", "env", "exit", NULL};
	int		i;

	if (!str || !ft_strcmp(str, ""))
		return (0);
	i = 0;
	while (b_in_list[i])
	{
		if (!ft_strcmp(b_in_list[i], str))
			return (i + 1);
		i++;
	}
	return (0);
}

t_l	*var_sub(t_l *head)
{
	t_l	*node;
	t_l	*next_node;
	char			*tmp;
	char			**t;
	int				i;

	next_node = head->next;
	tmp = str_dollar_sub(head->data); // node->data is freed.
	t = ft_strsplit(tmp, ' ');
	ft_strdel(&tmp);
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
		node->next = (t_l *)malloc(sizeof(t_l));
		node->next->data = ft_strdup(t[i]);
		node->next->next = NULL;
		node = node->next;
		i++;
	}
	node->next = next_node;
	return (head);
}

char	**get_arg_var_sub(t_simple_cmd *cmd)
{
	t_l	*list;
	t_l	*node;

	list = get_args(cmd);
	node = list;
	while (node)
	{
		if (is_dollar(node->data) > -1)
		{
			node = var_sub(node);
		}
		node = node->next;
	}
	return (list_to_tab(list));
}