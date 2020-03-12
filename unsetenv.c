/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 00:41:02 by sazouaka          #+#    #+#             */
/*   Updated: 2019/12/05 00:41:04 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "parse.h"
#include "builtins.h"

void	ft_unsetenv_1(char *flag)
{
	t_variable	*node;
	t_variable	*tmp1;

	node = g_var.var;
	while (node)
	{
		if (ft_strcmp(node->key, flag) == 0)
		{
			free(node->key);
			free(node->value);
			tmp1->next = node->next;
			free(node);
			return ;
		}
		tmp1 = node;
		node = node->next;
	}
}

int		ft_unsetenv(char **flag)
{
	int i;
	t_variable *node;

	node = g_var.var;
	if (flag[1] == NULL)
	{
		ft_putstr("unsetenv: Too few arguments.\n");
		return (1);
	}
	i = 1;
	while (flag[i])
	{
		if (node->env != 2)
			ft_unsetenv_1(flag[i]);
		else
		{
			ft_putstr("21sh: read-only variable: ");
			ft_putstr(flag[i]);
			ft_putchar('\n');
			return (1);
		}
		i++;
	}
	return (0);
}
