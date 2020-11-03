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

char	*tilde_sub_var(char *rest, char *tilde_prefix)
{
	char			*tmp;
	char			*s;
	struct passwd	*pw;

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
	else if (!ft_strcmp(tilde_prefix, ""))
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
	(str[i] == '/') ? (rest = ft_strdup(&(str[i]))) : (rest = ft_strdup(""));
	tilde_prefix = ft_strsub(str, 1, i - 1);
	s = tilde_sub_var(rest, tilde_prefix);
	if (s)
		ft_strdel(&str);
	else
		s = str;
	ft_strdel(&tilde_prefix);
	ft_strdel(&rest);
	return (s);
}

int		tilde_sub(t_list_token **cmd_token)
/*
**neeed to add ass_word
*/
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
		{
			str = tilde_sub_2(str);
/*
**tilde_sub_in_token()
*/
			if ((i = is_assword(node->data)))
			{
				node->data[i] = '\0';
/*
**!! free problem ?
*/
				tmp = ft_strjoin(node->data, str);
				ft_strdel(&(node->data));
				ft_strdel(&str);
				node->data = tmp;
			}
			else
			{
				ft_strdel(&(node->data));
				node->data = ft_strdup(str);
			}
		}
		ft_strdel(&str);
		node = node->next;
	}
	return (0);
}
