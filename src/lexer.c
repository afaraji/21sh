/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 23:14:10 by afaraji           #+#    #+#             */
/*   Updated: 2020/02/11 23:14:15 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

char	*fetch_variables(char *key, int typ)
{
	t_variable	*node;

	node = g_var.var;
	while (node)
	{
		if ((node->env == typ || typ < 0) && !ft_strcmp(key, node->key))
			return (ft_strdup(node->value));
		node = node->next;
	}
	return (NULL);
}

int		is_assword(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		return(i + 1);
	}
	return (0);
}

int		lexer(t_list_token **cmd_token)
{
	if (!cmd_token || !(*cmd_token))
		return (1);
	if (keywords_alias_sub(cmd_token))
	{
		g_var.exit_status = 42;
		return (42);
	}
//	4 - brace_expansion(cmd_token);  a{b,c} becomes ab ac
//	5 - sub_?  Substitutes the user’s home directory ($HOME) for tilde if it is at the beginning of a word
//	6 - sub_user_home(cmd_token); eg. ~USER
	tilde_sub(cmd_token);
//	7 - dollar_var_sub(cmd_token); eg. $HOME $PWD...		&	10 - split to tokens using isspace
	// dollar_sub(cmd_token);
//	8 - Does command substitution for any expression of the form $(string).		&	10 - split to tokens using isspace
//	9 - Evaluates arithmetic expressions of the form $((string)).		&	10 - split to tokens using isspace
//	11 - wilde_card_sub(cmd_token);
//	12 - lookup for cmd (1 - as it is like /bin/ls, 2 - builtin, 3 - in $PATH)
//	13 - runcmd after I/O affectation
	return (0);
}

// working on tilde_sub
