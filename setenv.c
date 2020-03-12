/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:33:31 by sazouaka          #+#    #+#             */
/*   Updated: 2019/12/03 21:33:45 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "parse.h"
#include "builtins.h"

int		ft_set_alnum(char **flag)
{
	int i;

	i = 1;
	while (flag[1][i])
	{
		if (!(ft_isalnum(flag[1][i])) && flag[1][i] != '_')
		{
			ft_putstr("setenv: Variable name must ");
			ft_putstr("contain alphanumeric characters.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int		ft_set_node(char **flag)
{
	t_variable	*node;

	node = g_var.var;
	while (node)
	{
		if (ft_strcmp(node->key, flag[1]) == 0)
		{
			if (flag[2] == NULL)
			{
				free(node->value);
				node->value = ft_strdup("");
			}
			else
			{
				free(node->value);
				node->value = ft_strdup(flag[2]);
			}
			return (0);
		}
		node = node->next;
	}
	return (1);
}

void	ft_set_lastnode(char **flag)
{
	t_variable	*node;

	node = g_var.var;
	while (node->next)
		node = node->next;
	node->next = (t_variable *)malloc(sizeof(t_variable));
	node = node->next;
	node->key = ft_strdup(flag[1]);
	if (flag[2] == NULL)
		node->value = ft_strdup("");
	else
		node->value = ft_strdup(flag[2]);
	node->next = NULL;
}

int		ft_setenv(char **flag)
{
	if (flag[1] != NULL && flag[2] != NULL && flag[3] != NULL)
	{
		ft_putstr("setenv: Too many arguments.\n");
		return (1);
	}
	else
	{
		if (flag[1] == NULL)
			print_env(0);
		else
		{
			if (!(ft_isalpha(flag[1][0])) && flag[1][0] != '_')
			{
				ft_putstr("setenv: Variable name must begin with a letter.\n");
				return (1);
			}
			else if (ft_set_alnum(flag) == 1)
				return (1);
			else if (ft_set_node(flag) == 1)
				return (1);
			ft_set_lastnode(flag);
		}
	}
	return (0);
}
