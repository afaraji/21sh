/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:39:19 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 17:39:45 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int				verify_tokens_error(int err, int typ)
{
	if (err == 2)
	{
		ft_putstr_fd("syntax error, unexpected token `", 2);
		g_var.errno = 130;
	}
	if (err == 3)
	{
		g_var.errno = 131;
		ft_putstr_fd("syntax error after `", 2);
	}
	if (err == 4)
	{
		ft_putstr_fd("syntax error, unexpected token `", 2);
		g_var.errno = 132;
	}
	ft_putstr_fd(tokentoa(typ), 2);
	ft_putstr_fd("'\n", 2);
	return (258);
}

int				verify_tokens(t_list_token *token)
{
	t_list_token	*node;
	t_list_token	*tmp;

	if (!token)
		return (1);
	if (ft_or(token->type, SMCLN, ANDLG, ORLG) ||
											ft_or(token->type, PIP, BGJOB, 0))
		return (verify_tokens_error(2, token->type));
	node = token;
	while (node)
	{
		if (ft_or(node->type, SMCLN, ANDLG, ORLG) || node->type == BGJOB)
		{
			tmp = node->next;
			while (tmp && tmp->type == SPACE)
				tmp = tmp->next;
			if (!tmp && (node->type == ANDLG || node->type == ORLG))
				return (verify_tokens_error(3, node->type));
			if (tmp && (ft_or(tmp->type, SMCLN, ANDLG, ORLG)
			|| tmp->type == BGJOB))
				return (verify_tokens_error(4, tmp->type));
		}
		node = node->next;
	}
	return (0);
}

char			*ft_4strjoin(char *s1, char *s2, char *s3, char *s4)
{
	char	*tmp1;
	char	*tmp2;
	char	*ret;

	tmp1 = ft_strjoin(s1, s2);
	tmp2 = ft_strjoin(s3, s4);
	ret = ft_strjoin(tmp1, tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (ret);
}

t_list_token	*get_last_node_toappend(t_list_token *tokens)
{
	t_list_token	*node;

	node = tokens;
	while (node->next)
		node = node->next;
	while (node && node->type == SPACE)
		node = node->prec;
	return (node);
}
