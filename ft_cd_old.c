/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_old.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:48:13 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/01 17:48:14 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

int	ft_cd_old(void)
{
	char	*old_d;
	char	*cwd;
	t_variable	*node;

	node = g_var.var;
	cwd = NULL;
	while (node)
	{
		if (ft_strcmp(node->key, "OLDPWD") == 0)
		{
			old_d = node->value;
			cwd = getcwd(NULL, 0);
			if (cwd)
				change_pwd("OLDPWD", cwd);
			chdir(old_d);
			change_pwd("PWD", cwd);
			return (0);
		}
		node = node->next;
	}
	ft_putstr(": No such file or directory.\n");
	return (1);
}
