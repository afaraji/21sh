/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:38:46 by sazouaka          #+#    #+#             */
/*   Updated: 2020/10/27 19:38:48 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

char	*history_search_num(int index)
{
	t_hist	*node;

	node = g_var.history;
	while (node->next)
		node = node->next;
	if (index < 0)
		index = node->index + index + 1;
	if (index < 1 || index > node->index)
		return (NULL);
	node = g_var.history;
	while (node)
	{
		if (node->index == index)
			return (ft_strdup(node->hist_str));
		node = node->next;
	}
	return (NULL);
}

char	*history_search_word(char *str)
{
	int		len;
	t_hist	*node;

	if (!str || !*str)
		return (NULL);
	node = g_var.history;
	len = ft_strlen(str);
	while (node->next)
		node = node->next;
	while (node)
	{
		if (!(ft_strncmp(str, node->hist_str, len)))
			return (ft_strdup(node->hist_str));
		node = node->prec;
	}
	return (NULL);
}

char	*history_search(char *str, t_hist **his_head)
{
	char	*cmd;

	if (!str || !(*his_head))
		return (NULL);
	if (ft_strcmp(str, "!") == 0)
		cmd = history_search_num(-1);
	else if ((is_all_digits(str) || (str[0] == '-' && is_all_digits(str + 1))))
		cmd = history_search_num(atoi(str));
	else
		cmd = history_search_word(str);
	return (cmd);
}
