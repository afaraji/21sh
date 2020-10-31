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
			ft_strdel(&tmp);
			tmp = ft_strsub_delimit(node->sub, ' ');
			if (!ft_strcmp(tmp, str))
			{
				ft_strdel(&tmp);
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
				ft_strdel(&(word->data));
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
	char *rsrved[17] = {"{", "}", "case", "do", "done", "elif", "else", "esac",
						"fi", "for", "if", "in", "then", "until", "while", ")", "("};
	int i;

	i = 0;
	while (i < 17)
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
	ft_strdel(&(node->data));
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
				ft_print(STDERR, "found '%s' - not implimented yet\n", node->data);
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

int		tilde_sub(t_list_token **cmd_token)// need to be normed and leak free
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
		if (node->type != WORD || (node->next && (node->next->type == QUOTE || node->next->type == DQUOTE)))
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
			i = 1;
			while (str[i] && str[i] != '/')
				i++;
			(str[i] == '/') ? (rest = ft_strdup(&(str[i]))) : (rest = ft_strdup(""));
			tilde_prefix = ft_strsub(str, 1, i - 1);
			if (!ft_strcmp(tilde_prefix, ""))
			{// $HOME
				tmp = fetch_variables("HOME", -1);
				if (tmp)
				{
					ft_strdel(&str);
					str = ft_strjoin(tmp, rest);
				}
				else
				{
					pw = getpwuid(getuid());
					ft_strdel(&str);
					if (pw)
						str = ft_strjoin(pw->pw_dir, rest);
				}
			}
			else if(!ft_strcmp(tilde_prefix, "-"))
			{// $OLDPWD | ~-
				tmp = fetch_variables("OLDPWD", -1);
				if(tmp)
				{
					ft_strdel(&str);
					str = ft_strjoin(tmp, rest);
				}
			}
			else if (!ft_strcmp(tilde_prefix, "+"))
			{// $PWD
				tmp = fetch_variables("PWD", -1);
				if(tmp)
				{
					ft_strdel(&str);
					str = ft_strjoin(tmp, rest);
				}
			}
			else
			{
				tmp = ft_strjoin("/Users/", tilde_prefix);
				if (!access(tmp, F_OK))
				{
					ft_strdel(&str);
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
				ft_strdel(&(node->data));
				ft_strdel(&str);
				node->data = tmp;
			}
			else
			{
				ft_strdel(&(node->data));
				node->data = str;
			}
		}
		node = node->next;
	}
	return (0);
}

int		is_dollar(char *s)
{
	int i;
	if (!s)
		return (-42);
	i = 0;
	while(s[i] && s[i] != '$')
		i++;
	if (s[i] == '$')
		return (i);
	return (-42);
}

int		end_dollar_word(char *s, int start)
{
	int i;
	int bracket;

	bracket = 0;
	if (s[start + 1] == '{')
		bracket = 1;
	i = start + bracket + 1;
	if (s[i] == '!' || s[i] == '#' || s[i] == '$' || s[i] == '?')
		return(i + 1 + bracket);
	if (s[i] != '_' && !ft_isalpha(s[i]))
	{
		if (!bracket)
			return (i);
		return (-1);
	}
	while (s[i] && (s[i] == '_' || ft_isalnum(s[i])))
		i++;
	if (bracket)
	{
		if (s[i] == '}')
			return (i + 1);
		else
			return (-1);
	}
	return (i);
}

char	*get_dollar_var(char *s, int start, int end)
{
	char	*tmp;
	char	*var;
	int		index;
	int		len;

	if (start == end - 1)
		return (ft_strdup("$"));
	index = start + 1;
	len = end - start - 1;
	if (s[index] == '{' && s[index + len - 1] == '}')
	{
		index++;
		len -= 2;
	}
	tmp = ft_strsub(s, index, len);
	var = fetch_variables(tmp, -1);
	if (!var)
		return(ft_strdup(""));
	return (var);
}

char		*str_dollar_sub(char *str)
{
	int		start;
	int		end;
	char	*prefix;
	char	*suffix;
	char	*var;

	start = is_dollar(str);
	end = end_dollar_word(str, start);
	if (start < 0 || end < 0)
		return (str);
	prefix = ft_strsub(str, 0, start);
	var = get_dollar_var(str, start, end);
	suffix = ft_strjoin(var, &(str[end]));
	ft_strdel(&str);
	str = ft_strjoin(prefix, suffix);
	ft_strdel(&prefix);
	ft_strdel(&var);
	ft_strdel(&suffix);
	if (is_dollar(str) >= 0 && (end - start) > 1)
		str = str_dollar_sub(str);
	return (str);
}

int		dollar_sub(t_list_token **cmd_token)
{
	t_list_token	*node;

	node = *cmd_token;
	while (node)
	{
		if (node->type == WORD && is_dollar(node->data) >= 0)
		{
			node->data = str_dollar_sub(node->data);
		}
		node = node->next;
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
