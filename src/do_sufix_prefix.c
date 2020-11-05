/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_sufix_prefix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:21:00 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 18:23:09 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int		env_tab_count(int all)
{
	t_variable	*node;
	int			count;

	node = g_var.var;
	count = 0;
	while (node)
	{
		if (node->env == 0 || all)
			count++;
		node = node->next;
	}
	return (count);
}

char	**env_to_tab(t_variable *var, int all)
{
	t_variable	*node;
	char		**argv;
	char		*tmp;
	int			i;

	node = var;
	i = env_tab_count(all);
	if (!(argv = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (node)
	{
		if (node->env == 0 || all)
		{
			tmp = ft_strjoin(node->key, "=");
			argv[i] = ft_strjoin(tmp, node->value);
			ft_strdel(&tmp);
			i++;
		}
		node = node->next;
	}
	argv[i] = NULL;
	if (i == 0)
		return (NULL);
	return (argv);
}

int		do_suffix(t_cmd_suffix *suffix)
{
	t_cmd_suffix	*node;
	int				ret;

	ret = 0;
	node = suffix;
	while (node)
	{
		if (node->io_redirect)
		{
			ret = do_redirect(node->io_redirect);
			if (ret != 0)
				return (ret);
		}
		node = node->suffix;
	}
	return (ret);
}

int		do_simple_cmd(t_simple_cmd *cmd)
{
	int		ret;

	ret = 0;
	if (cmd->prefix)
	{
		ret = do_prefix(cmd->prefix, g_var.var, 0);
	}
	if (ret != 0)
		return (ret);
	if ((cmd->name || cmd->word) && cmd->suffix)
	{
		ret = do_suffix(cmd->suffix);
	}
	return (ret);
}
