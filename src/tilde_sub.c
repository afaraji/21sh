/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:56:34 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 18:56:51 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

char	*tilde_sub_var_2(char *tilde_prefix, char *rest)
{
	struct passwd	*pw;
	char			*s;
	char			*tmp;

	s = NULL;
	if (!ft_strcmp(tilde_prefix, ""))
	{
		pw = getpwuid(getuid());
		if (pw)
			s = ft_strjoin(pw->pw_dir, rest);
	}
	else
	{
		tmp = ft_strjoin("/Users/", tilde_prefix);
		if (!access(tmp, F_OK))
			s = ft_strjoin(tmp, rest);
		ft_strdel(&tmp);
	}
	return (s);
}

char	*tilde_sub_var(char *rest, char *tilde_prefix)
{
	char			*tmp;
	char			*s;

	tmp = NULL;
	if (!ft_strcmp(tilde_prefix, ""))
		tmp = fetch_variables("HOME", -1);
	else if (!ft_strcmp(tilde_prefix, "-"))
		tmp = fetch_variables("OLDPWD", -1);
	else if (!ft_strcmp(tilde_prefix, "+"))
		tmp = fetch_variables("PWD", -1);
	s = NULL;
	if (tmp)
		s = ft_strjoin(tmp, rest);
	else
	{
		s = tilde_sub_var_2(tilde_prefix, rest);
	}
	ft_strdel(&tmp);
	return (s);
}

char	*tilde_sub_2(char *str)
{
	char	*s;
	char	*tilde_prefix;
	char	*rest;
	int		i;

	s = NULL;
	i = 1;
	while (str[i] && str[i] != '/')
		i++;
	if (str[i] == '/')
		rest = ft_strdup(&(str[i]));
	else
		rest = ft_strdup("");
	tilde_prefix = ft_strsub(str, 1, i - 1);
	s = tilde_sub_var(rest, tilde_prefix);
	if (!s)
		s = ft_strdup(str);
	ft_strdel(&tilde_prefix);
	ft_strdel(&rest);
	return (s);
}

char	*tilde_sub_3(char *node, char *str)
{
	int		i;
	char	*ret;

	if ((i = is_assword(node)))
	{
		node[i] = '\0';
		ret = ft_strjoin(node, str);
	}
	else
	{
		ret = ft_strdup(str);
	}
	ft_strdel(&node);
	ft_strdel(&str);
	return (ret);
}

int		tilde_sub(t_list_token **cmd_token)
{
	char			*tmp;
	char			*str;
	t_list_token	*node;
	int				i;

	node = *cmd_token;
	tmp = NULL;
	while (node)
	{
		if (node->type != WORD || (node->next && (node->next->type == QUOTE
		|| node->next->type == DQUOTE)))
		{
			node = node->next;
			continue;
		}
		if ((i = is_assword(node->data)))
			str = ft_strdup(&(node->data[i]));
		else
			str = ft_strdup(node->data);
		if (str && str[0] == '~')
			node->data = tilde_sub_3(node->data, tilde_sub_2(str));
		ft_strdel(&str);
		node = node->next;
	}
	return (0);
}
