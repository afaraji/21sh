/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_completion_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 19:33:46 by sazouaka          #+#    #+#             */
/*   Updated: 2020/10/02 19:33:48 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

t_l				*get_cmd_list_1(char *str, t_l *head)
{
	t_l	*node;

	if (!head)
	{
		if (!(head = (t_l *)malloc(sizeof(t_l))))
			return (NULL);
		head->data = ft_strdup(str);
		head->next = NULL;
		return (head);
	}
	node = head;
	while (node->next)
		node = node->next;
	if (!(node->next = (t_l *)malloc(sizeof(t_l))))
		return (NULL);
	node = node->next;
	node->data = ft_strdup(str);
	node->next = NULL;
	return (head);
}

t_l				*search_builtin(char *str)
{
	int		i;
	t_l		*head;
	char	**builtins_list;

	i = 0;
	head = NULL;
	builtins_list = ft_strsplit(BUILTINS, '|');
	while (builtins_list[i])
	{
		if (!ft_strncmp(builtins_list[i], str, ft_strlen(str)))
			head = get_cmd_list_1(builtins_list[i], head);
		i++;
	}
	free_tab(builtins_list);
	return (head);
}

int				get_path_value(char ***str)
{
	t_variable	*var;

	var = g_var.var;
	while (var)
	{
		if (!ft_strcmp(var->key, "PATH"))
		{
			*str = ft_strsplit(var->value, ':');
			return (1);
		}
		var = var->next;
	}
	return (0);
}
