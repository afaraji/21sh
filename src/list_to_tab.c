/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:37:17 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/04 16:37:24 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int		list_count(t_l *list)
{
	t_l	*node;
	int	i;

	node = list;
	i = 0;
	while (node)
	{
		if (ft_strcmp(node->data, ""))
			i++;
		node = node->next;
	}
	return (i + 1);
}

char	**list_to_tab(t_l *list)
{
	t_l		*node;
	int		i;
	char	**args;

	if (!list)
		return (NULL);
	if (!(args = (char **)malloc(sizeof(char *) * list_count(list))))
		return (NULL);
	node = list;
	i = 0;
	while (node)
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
