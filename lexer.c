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

char	*ft_appendstr(char *s1, char *s2)
{
	char	*joined;
	char	*tmp;

	if (!s1 || !s2)
	{
		if (s1)
			return (s1);
		if (s2)
			return (s2);
		return(NULL);
	}
	tmp = ft_strjoin(s1, "\n");
	joined = ft_strjoin(tmp, s2);
	ft_strdel(&tmp);
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (joined);
}

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
				fprintf(ttyfd, "------|%s|-----\n", word->data);
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

void		insert_alias(char *key, char *sub)
{
	t_alias		*node;

	if (g_var.aliases)
	{
		node = g_var.aliases;
		while (node->next)
			node = node->next;
		node->next = (t_alias *)malloc(sizeof(t_alias));
		node->next->next = NULL;
		node->next->key = ft_strdup(key);
		node->next->sub = ft_strdup(sub);		
	}
	else
	{
		g_var.aliases = (t_alias *)malloc(sizeof(t_alias));
		g_var.aliases->next = NULL;
		g_var.aliases->key = ft_strdup(key);
		g_var.aliases->sub = ft_strdup(sub);
	}
	
}

void	get_aliases(void)
{
	insert_alias("toto", "lala qwerty");
	insert_alias("lala", "yoyo");
	insert_alias("yoyo", "test alias");
	insert_alias("abc", "abce lol  123");
}

t_list_token	*__tokenize(char *str);
void	token_print(t_list_token *node); 

void	parse_and_replace(t_list_token **cmd_token, t_list_token *node)
{
	t_list_token	*toinsert;
	t_list_token	*tmp;

	toinsert = __tokenize(node->data);
	tmp = toinsert;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node->next;
	if (node->next)
		node->next->prec = tmp;
	if (node->prec)
	{
		tmp = node->prec;
		toinsert->prec = tmp;
		tmp->next = toinsert;
	}
	else
	{
		*cmd_token = toinsert;
	}
	free(node->data);
	free(node);	
}

int		keywords_alias_sub(t_list_token **cmd_token)
{
	t_list_token *node;

	node = *cmd_token;
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
				printf("\nfound '%s' - not implimented yet", node->data);
				return (1);
			}
			else if (node && node->type == WORD)
			{
				if (alias_sub(node, g_var.aliases))
				{
					parse_and_replace(cmd_token, node);
					if (keywords_alias_sub(cmd_token))
						return (1);
					return (0); // should break or return ??? break == return unless there is code after while
				}
			}
		}
		if (node)
			node = node->next;
	}
	return (0);
}

char	*fetch_variables(char *key, int typ)
{
	t_variable	*node;

	node = g_var.var;
	while (node)
	{
		if (node->env == typ && !ft_strcmp(key, node->key))
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

int		tilde_sub2(char *str)
{
	char 			*tmp = NULL;
	char 			*tilde_prefix;
	char 			*rest;
	t_list_token	*node;
	struct passwd	*pw;
	int				i;

	if (str[0] == '~')
	{
		i = 1;
		while (str[i] && str[i] != '/')
			i++;
		(str[i] == '/') ? (rest = ft_strdup(&str[i])) : (rest = ft_strdup(""));
		tilde_prefix = ft_strsub(str, 1, i - 1);
		if (!ft_strcmp(tilde_prefix, ""))
		{// $HOME
			tmp = fetch_variables("HOME", 0);
			if (tmp)
			{
				free(str);
				str = ft_strjoin(tmp, rest);
			}
			else
			{
				pw = getpwuid(getuid());
				free(str);
				str = ft_strjoin(pw->pw_dir, rest);
			}
		}
		else if(!ft_strcmp(tilde_prefix, "-"))
		{// $OLDPWD | ~-
			tmp = fetch_variables("OLDPWD", 0);
			if(tmp)
			{
				free(str);
				str = ft_strjoin(tmp, rest);
			}				
		}
		else if (!ft_strcmp(tilde_prefix, "+"))
		{// $PWD
			tmp = fetch_variables("PWD", 0);
			if(tmp)
			{
				free(str);
				str = ft_strjoin(tmp, rest);
			}
		}
		else
		{
			fprintf(ttyfd, "===========|%s|\n", tilde_prefix);
			tmp = ft_strjoin("/Users/", tilde_prefix);
			if (!access(tmp, F_OK))
			{
				fprintf(ttyfd, "===========|%s%s|____\n", tmp, rest);
				free(str);
				str = ft_strjoin(tmp, rest);
			}
		}
		ft_strdel(&rest);
		ft_strdel(&tilde_prefix);
		ft_strdel(&tmp);
	}
	return (0);
}

int		is_assword(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		return(i + 1);
	}
	return (0)
}

int		tilde_sub(t_list_token **cmd_token)
{// neeed to add ass_word
	char 			*tmp = NULL;
	char			*str;
	char 			*tilde_prefix;
	char 			*rest;
	t_list_token	*node;
	struct passwd	*pw;
	int				i;

	node = *cmd_token;
	while (node)
	{
		if (node->type == WORD && (i = is_assword(node->data)))
			str = ft_strdup(&(node->data[i]))
		else if (node->type == WORD)
			str = ft_strdup(node->data);
		if (str && str[0] == '~')
		{
			i = 1;
			while (str[i] && str[i] != '/')
				i++;
			(str[i] == '/') ? (rest = ft_strdup(&(str[i]))) : (rest = ft_strdup(""));
			tilde_prefix = ft_strsub(str, 1, i - 1);
			if (!ft_strcmp(tilde_prefix, ""))
			{// $HOME
				tmp = fetch_variables("HOME", 0);
				if (tmp)
				{
					free(str);
					str = ft_strjoin(tmp, rest);
				}
				else
				{
					pw = getpwuid(getuid());
					free(str);
					str = ft_strjoin(pw->pw_dir, rest);
				}
			}
			else if(!ft_strcmp(tilde_prefix, "-"))
			{// $OLDPWD | ~-
				tmp = fetch_variables("OLDPWD", 0);
				if(tmp)
				{
					free(str);
					str = ft_strjoin(tmp, rest);
				}				
			}
			else if (!ft_strcmp(tilde_prefix, "+"))
			{// $PWD
				tmp = fetch_variables("PWD", 0);
				if(tmp)
				{
					free(str);
					str = ft_strjoin(tmp, rest);
				}
			}
			else if (node->next->type != QUOTE && node->next->type != DQUOTE)
			{
				fprintf(ttyfd, "===========|%s|\n", tilde_prefix);
				tmp = ft_strjoin("/Users/", tilde_prefix);
				if (!access(tmp, F_OK))
				{
					fprintf(ttyfd, "===========|%s%s|____\n", tmp, rest);
					free(str);
					str = ft_strjoin(tmp, rest);
				}
			}
			ft_strdel(&rest);
			ft_strdel(&tilde_prefix);
			if (tmp)
				ft_strdel(&tmp);
			if ((i = is_assword(node->data)))
			{
				node->data[i] = '\0';
				tmp = ft_strjoin(node->data, str);
				free(node->data);
				free(str);
				node->data = tmp;
			}
			else
			{
				free(node->data);
				node->data = str;
			}
		}
		node = node->next;
	}
	return (0);
}

int		dollar_sub(t_list_token **cmd_token)
{
	
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
	dollar_sub(cmd_token);
//	8 - Does command substitution for any expression of the form $(string).		&	10 - split to tokens using isspace
//	9 - Evaluates arithmetic expressions of the form $((string)).		&	10 - split to tokens using isspace
//	11 - wilde_card_sub(cmd_token);
//	12 - lookup for cmd (1 - as it is like /bin/ls, 2 - builtin, 3 - in $PATH)
//	13 - runcmd after I/O affectation
	return (0);
}