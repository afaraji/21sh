/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_completion.c                             :+:      :+:    :+:   */
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

t_l				*get_var_list(char *str, t_l *head)
{
	t_l		*node;
	char	*tmp;

	if (!head)
	{
		if (!(head = (t_l *)malloc(sizeof(t_l))))
			return (NULL);
		tmp = ft_strdup(str);
		head->data = ft_strjoin("$", tmp);
		ft_strdel(&tmp);
		head->next = NULL;
		return (head);
	}
	node = head;
	while (node->next)
		node = node->next;
	if (!(node->next = (t_l *)malloc(sizeof(t_l))))
		return (NULL);
	node = node->next;
	tmp = ft_strdup(str);
	node->data = ft_strjoin("$", tmp);
	ft_strdel(&tmp);
	node->next = NULL;
	return (head);
}

char			**var_search(char *str)
{
	t_variable	*var;
	t_l			*var_list;
	char		**var_tab;

	var = g_var.var;
	var_list = NULL;
	var_tab = NULL;
	while (var)
	{
		if (!ft_strncmp(str, var->key, ft_strlen(str)))
			var_list = get_var_list(var->key, var_list);
		var = var->next;
	}
	var_tab = tab_from_list(var_list);
	free_list(var_list);
	return (var_tab);
}
