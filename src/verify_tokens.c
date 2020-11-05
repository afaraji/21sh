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

int		verify_tokens_error(int err, int typ)
{
	ft_putstr_fd("syntax error, unexpected token `", 2);
	ft_putstr_fd(tokentoa(typ), 2);
	ft_putstr_fd("'\n", 2);
	if (err == 2)
	{
		g_var.errno = 130;
		return (2);
	}
	if (err == 3)
	{
		g_var.errno = 131;
		return (3);
	}
	if (err == 4)
	{
		g_var.errno = 132;
		return (4);
	}
	return (0);
}

int		verify_tokens(t_list_token *token)
{
	t_list_token	*node;
	t_list_token	*tmp;

	if (!token)
		return (1);
	if (ft_or(token->type, SMCLN, ANDLG, ORLG)
	|| ft_or(token->type, PIP, BGJOB, 0))
		return (verify_tokens_error(2, token->type));
	node = token;
	while (node)
	{
		if (ft_or(token->type, SMCLN, ANDLG, ORLG) || token->type == BGJOB)
		{
			tmp = node->next;
			while (tmp && tmp->type == SPACE)
				tmp = tmp->next;
			if (!tmp && (node->type == ANDLG || node->type == ORLG))
				return (verify_tokens_error(3, node->type));
			if (tmp && (ft_or(token->type, SMCLN, ANDLG, ORLG)
			|| token->type == BGJOB))
				return (verify_tokens_error(4, tmp->type));
		}
		node = node->next;
	}
	return (0);
}
