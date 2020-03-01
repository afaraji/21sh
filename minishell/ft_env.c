/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:53:27 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/01 17:53:29 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*ft_get_node(char *str)
{
	t_lst	*node;
	int		i;

	node = (t_lst *)malloc(sizeof(t_lst));
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			node->name = ft_strsub(str, 0, i);
			break ;
		}
		i++;
	}
	node->content = ft_strdup(&str[i + 1]);
	node->next = NULL;
	return (node);
}

t_lst	*ft_env(char **env)
{
	t_lst	*head;
	t_lst	*node;
	int		i;

	head = ft_get_node(PATH_D);
	i = 0;
	node = head;
	while (env[i])
	{
		node->next = ft_get_node(env[i]);
		node = node->next;
		i++;
	}
	return (head);
}

void	ft_printlist(t_lst *head)
{
	t_lst	*node;

	node = head->next;
	while (node)
	{
		ft_putstr(node->name);
		ft_putchar('=');
		ft_putstr(node->content);
		ft_putchar('\n');
		node = node->next;
	}
}
