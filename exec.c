/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:13:41 by afaraji           #+#    #+#             */
/*   Updated: 2020/02/10 16:14:17 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	**simplecmd_to_tab(t_simple_cmd *cmd)
{

}

int		env_tab_count(void)
{
	t_variable	*node;
	int			count;
	
	node = g_var.var;
	count = 0;
	while (node)
	{
		if (node->env == 0)
			count++;
		node = node->next;
	}
	return (count);
}

char	**env_to_tab(void)
{
	t_variable	*node;
	int			count;
	char		*argv;
	char		*tmp;
	int			i;
	
	node = g_var.var;
	i = 0;
	count = env_tab_count();	
	argv = (char **)malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	while (node)
	{
		if (node->env == 0)
		{
			tmp = ft_strjoin(node->key, "=");
			argv[i] = ft_strjoin(tmp, node->value);
			free(tmp);
			i++;
		}
		node = node->next;
	}
	argv[i] = NULL;
	if (i == 0)
		return (NULL);
	return (argv);
}