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

#include "parse.h"

char	*ft_strsub_delimit(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	return (ft_strsub(s, 0, i));
}

int		alias_infinit_loop(char *str, t_alias *aliases)
{
	char *tmp;
	t_alias *node;

	node = aliases;
	tmp = ft_strdup(str);
	while (node)
	{
		if (!ft_strcmp(tmp, node->key))
		{
			free(tmp);
			tmp = ft_strsub_delimit(node->sub, ' ');
			if (!ft_strcmp(tmp, str))
			{
				free(tmp);
				return (1);
			}
			else
				node = aliases;
		}
		node = node->next;
	}

	return (0);
}

int		alias_sub(t_list_token *word, t_alias *aliases)
{
	t_alias	*node;

	node = aliases;
	while (node)
	{
		if (!ft_strcmp(word->data, node->key))
		{
			if(!alias_infinit_loop(node->key, aliases))
			{
				free(word->data);
				word->data = ft_strdup(node->sub);
				return (1);
			}
		}
		node = node->next;
	}
	return(0);
}

int		is_reserved(char *str)
{
	char *rsrved[18] = {"!", "{", "}", "case", "do", "done", "elif", "else", "esac",
						"fi", "for", "if", "in", "then", "until", "while", ")", "("};
	int i;

	i = 0;
	while (i < 18)
	{
		if (ft_strcmp(str, rsrved[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

t_alias		*get_aliases(void)
{
	t_alias		*aliases;
	t_alias		*node;

	aliases = (t_alias *)malloc(sizeof(t_alias));
	aliases->key = ft_strdup("toto");
	aliases->sub = ft_strdup("tata hahahahah");
	aliases->next = (t_alias *)malloc(sizeof(t_alias));
	node = aliases->next;
	node->key = ft_strdup("tata");
	node->sub = ft_strdup("lolo");
	node->next = (t_alias *)malloc(sizeof(t_alias));
	node = node->next;
	node->key = ft_strdup("lolo");
	node->sub = ft_strdup("samsam khayba");
	node->next = NULL;
	return (aliases);
}

t_list_token	*__tokenize(char *str);
void	token_print(t_list_token *node);

void	parse_and_replace(t_list_token **cmd_token, t_list_token *node)
{
	// parse node->data and insert it and replace wit it node.
	t_list_token *prec = node->prec;
	t_list_token *next = node->next;
	t_list_token *to_insert;

	to_insert = __tokenize(node->data);
	prec->next = to_insert;
	to_insert->prec = prec;
	while(to_insert->next)
		to_insert = to_insert->next;
	to_insert->next = next;
	next->prec = to_insert;
	// should free node;
}

int		keywords_alias_sub(t_list_token **cmd_token)
{
	t_list_token *node;

	node = *cmd_token;
	//give head to be treated.
	while (node)
	{
		if(_OR(node->type, SMCLN, ANDLG, ORLG, PIP, BGJOB) || node == *cmd_token)
		{
			if (node != *cmd_token)
				node = node->next;
			while (node && node->type == SPACE)
				node = node->next;
			if (node && node->type == WORD && is_reserved(node->data))
			{
				printf("found '%s' - not implimented yet\n", node->data);
				return (1);
			}
			else if (node && node->type == WORD)
			{
				if (alias_sub(node, get_aliases()))
				{
					parse_and_replace(cmd_token, node);
					keywords_alias_sub(cmd_token);
					return (2); // should break or return ??? break == return unless there is code after while
				}
			}
			
		}
		node = node->next;
	}

	// after the while should be brace expension.
	return (0);
}

int		lexer(t_list_token **cmd_token)
{
	keywords_alias_sub(cmd_token);
//	brace_expansion(cmd_token);
//	sub_?  Substitutes the user’s home directory ($HOME) for tilde if it is at the beginning of a word
//	sub_user_home(cmd_token); eg. ~USER
//	7 - dollar_var_sub(cmd_token); eg. $HOME $PWD...		&	10 - split to tokens using isspace
//	8 - Does command substitution for any expression of the form $(string).		&	10 - split to tokens using isspace
//	9 - Evaluates arithmetic expressions of the form $((string)).		&	10 - split to tokens using isspace
//	11 - wilde_card_sub(cmd_token);
//	12 - lookup for cmd (1 - as it is like /bin/ls, 2 - builtin, 3 - in $PATH)
//	13 - runcmd after I/O affectation
	return (0);
}