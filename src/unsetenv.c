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

#include "../inc/ft_21sh.h"

void	delete_node(t_variable *prec, t_variable *current, t_variable *after)
{
	prec->next = after;
	current->next = NULL;
	free(current->key);
	free(current->value);
	free(current);
}

int		ft_unsetenv(char **flag)
{
	int			i;
	t_variable	*node;
	t_variable	*prec;

	if (flag[1] == NULL)
	{
		ft_putstr_fd("unsetenv: Too few arguments.\n", STDERR);
		return (1);
	}
	i = 1;
	while (flag[i])
	{
		node = g_var.var;
		prec = NULL;
		while (node)
		{
			if (!ft_strcmp(node->key, flag[i]))
			{
				if (node->env != 2)
					delete_node(prec, node, node->next);
				else
				{
					ft_putstr_fd("unsetenv: read-only variable: ", STDERR);
					ft_putstr_fd(flag[i], STDERR);
					ft_putchar_fd('\n', STDERR);
				}
				break;
			}
			prec = node;
			node = node->next;
		}
		i++;
	}
	return (0);
}
