/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_translate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:17:32 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 17:17:37 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int		is_op_2(char c, char c2)
{
	if (c == '<' && c2 == '<')
		return (SMLSML);
	if (c == '>')
		return (GRT);
	if (c == '<')
		return (SML);
	if (c == '&')
		return (BGJOB);
	return (0);
}

int		is_op(char *str, int i)
{
	if (ft_isspace(str[i]))
		return (SPACE);
	if (str[i] == 39)
		return (QUOTE);
	if (str[i] == '"')
		return (DQUOTE);
	if (str[i] == ';')
		return (SMCLN);
	if (str[i] == '&' && str[i + 1] == '&')
		return (ANDLG);
	if (str[i] == '|' && str[i + 1] == '|')
		return (ORLG);
	if (str[i] == '|')
		return (PIP);
	if (str[i] == 92)
		return (ESCAPE);
	if ((str[i] == '>' && str[i + 1] == '&') ||
						(str[i] == '&' && str[i + 1] == '>'))
		return (GRTAND);
	if (str[i] == '>' && str[i + 1] == '>')
		return (GRTGRT);
	if ((str[i] == '<' && str[i + 1] == '&'))
		return (SMLAND);
	return (is_op_2(str[i], str[i + 1]));
}

char	*tokentoa_2(int token)
{
	if (token == SMLSML)
		return ("<<");
	if (token == SMLAND)
		return ("<&");
	if (token == GRTAND)
		return (">&");
	return (ft_itoa(token));
}

char	*tokentoa(int token)
{
	if (token == SPACE)
		return (" ");
	if (token == QUOTE)
		return ("'");
	if (token == DQUOTE)
		return ("\"");
	if (token == SMCLN)
		return (";");
	if (token == ANDLG)
		return ("&&");
	if (token == ORLG)
		return ("||");
	if (token == PIP)
		return ("|");
	if (token == BGJOB)
		return ("&");
	if (token == ESCAPE)
		return ("\\");
	if (token == GRT)
		return (">");
	if (token == GRTGRT)
		return (">>");
	if (token == SML)
		return ("<");
	return (tokentoa_2(token));
}
