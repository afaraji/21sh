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

int	ft_cd_old(t_lst *head)
{
	char	*buff;
	char	*old_d;
	t_lst	*node;

	node = head;
	while (node)
	{
		if (ft_strcmp(node->name, "OLDPWD") == 0)
		{
			if (!(buff = (char *)malloc(sizeof(char) * 1000)))
				return (1);
			old_d = node->content;
			if (getcwd(buff, 500))
				ft_change_d(head, "OLDPWD", getcwd(buff, 500));
			chdir(old_d);
			ft_change_d(head, "PWD", getcwd(buff, 500));
			free(buff);
			return (0);
		}
		node = node->next;
	}
	ft_putstr(": No such file or directory.\n");
	return (1);
}
