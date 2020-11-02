/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:46:40 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/01 17:46:42 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int	change_pwd(char *str1, char *str2)
{
	t_variable	*node;

	if (!g_var.var || !str2)
		return (1);
	node = g_var.var;
	while (node)
	{
		if (ft_strcmp(node->key, str1) == 0)
		{
			free(node->value);
			node->value = ft_strdup(str2);
			return (0);
		}
		node = node->next;
	}
	node = g_var.var;
	while (node->next)
		node = node->next;
	if (!(node->next = (t_variable *)malloc(sizeof(t_variable))))
		return (1);
	node = node->next;
	node->key = ft_strdup(str1);
	node->value = ft_strdup(str2);
	node->next = NULL;
	return (0);
}
