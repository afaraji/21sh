/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:24:05 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 17:24:11 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

t_list_token	*add_quote(int *index, char *str)
{
	t_list_token	*node;
	int				i;

	i = *index;
	if (!(node = (t_list_token *)malloc(sizeof(t_list_token))))
		return (NULL);
	i++;
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] == '\'')
		node->is_ok = 1;
	else
		node->is_ok = 0;
	node->type = QUOTE;
	node->data = ft_strsub(str, *index + 1, i - *index - 1);
	node->next = NULL;
	node->prec = NULL;
	if (i + 1 < (int)ft_strlen(str))
		*index = i + 1;
	else
		*index = ft_strlen(str);
	return (node);
}

t_list_token	*add_dquote(int *index, char *str)
{
	t_list_token	*node;
	int				i;

	i = *index;
	node = (t_list_token *)malloc(sizeof(t_list_token));
	if (!node)
		return (NULL);
	i++;
	while (str[i] && (str[i] != '"' || str[i - 1] == '\\'))
		i++;
	node->is_ok = (str[i] == '"') ? 1 : 0;
	node->type = DQUOTE;
	node->data = (ft_strsub(str, *index + 1, i - *index - 1));
	if (is_dollar(node->data) >= 0)
		node->data = str_dollar_sub(node->data);
	node->data = delete_escape(node->data);
	node->next = NULL;
	node->prec = NULL;
	if (i + 1 < (int)ft_strlen(str))
		*index = i + 1;
	else
		*index = ft_strlen(str);
	return (node);
}

t_list_token	*add_space(int *index, char *str)
{
	t_list_token	*node;
	int				i;

	i = *index;
	node = (t_list_token *)malloc(sizeof(t_list_token));
	if (!node)
		return (NULL);
	node->type = SPACE;
	node->data = NULL;
	node->next = NULL;
	node->prec = NULL;
	while (ft_isspace(str[i]))
		i++;
	*index = i;
	return (node);
}

t_list_token	*add_escape(int *index, char *str)
{
	t_list_token	*node;

	node = (t_list_token *)malloc(sizeof(t_list_token));
	if (!node)
		return (NULL);
	node->type = WORD;
	if (!ft_strcmp(&str[*index], "\\"))
	{
		node->data = ft_strdup("\n");
		node->type = ESCAPE;
	}
	else
		node->data = ft_strsub(str, *index + 1, 1);
	node->next = NULL;
	node->prec = NULL;
	*index += 2;
	return (node);
}

t_list_token	*add_op(int *index, int op)
{
	t_list_token	*node;

	node = (t_list_token *)malloc(sizeof(t_list_token));
	if (!node)
		return (NULL);
	if (op == ANDLG || op == ORLG || op == GRTGRT || op == SMLSML)
		*index += 1;
	if (op == SMLAND || op == GRTAND)
		*index += 1;
	*index += 1;
	node->type = op;
	node->data = NULL;
	node->next = NULL;
	node->prec = NULL;
	return (node);
}
