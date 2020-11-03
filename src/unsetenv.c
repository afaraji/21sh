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
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

void	delete_node(t_variable *prec, t_variable *current, t_variable *after)
{
	prec->next = after;
	current->next = NULL;
	free(current->key);
	free(current->value);
	free(current);
}

int		ft_unsetenv_2(char *str)
{
	t_variable	*node;
	t_variable	*prec;

	node = g_var.var;
	prec = NULL;
	while (node)
	{
		if (!ft_strcmp(node->key, str))
		{
			if (node->env != 2)
			{
				delete_node(prec, node, node->next);
				return (0);
			}
			else
			{
				ft_print(STDERR, "unsetenv: read-only variable: %s\n", str);
				return (1);
			}
		}
		prec = node;
		node = node->next;
	}
	return (0);
}

int		ft_unsetenv(char **flag)
{
	int			i;
	int			ret;
	int			tmp;

	ret = 0;
	if (flag[1] == NULL)
	{
		ft_putstr_fd("unsetenv: Too few arguments.\n", STDERR);
		return (1);
	}
	i = 1;
	while (flag[i])
	{
		tmp = ft_unsetenv_2(flag[i]);
		if (tmp)
			ret = tmp;
		i++;
	}
	return (ret);
}
