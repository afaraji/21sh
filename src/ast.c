/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:35:31 by afaraji           #+#    #+#             */
/*   Updated: 2020/10/31 20:52:37 by afaraji          ###   ########.fr       */
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
	if ((str[i] == '<' && str[i + 1] == '&'))// || (str[i] == '&' && str[i + 1] == '<'))
		return (SMLAND);
	return (is_op_2(str[i], str[i + 1]));
}

char	*tokentoa_2(int token)
{
	if (token == SMLSML)
		return("<<");
	if (token == SMLAND)
		return("<&");
	if (token == GRTAND)
		return(">&");
	return(ft_itoa(token));
}

char	*tokentoa(int token)
{
	if (token == SPACE)
		return (" ");
	if (token == QUOTE)
		return("'");
	if (token == DQUOTE)
		return("\"");
	if (token == SMCLN)
		return(";");
	if (token == ANDLG)
		return("&&");
	if (token == ORLG)
		return("||");
	if (token == PIP)
		return("|");
	if (token == BGJOB)
		return("&");
	if (token == ESCAPE)
		return("\\");
	if (token == GRT)
		return(">");
	if (token == GRTGRT)
		return(">>");
	if (token == SML)
		return("<");
	return (tokentoa_2(token));
}


t_list_token	*add_quote(int *index, char *str)
{
	t_list_token	*node;
	int i = *index;

	if (!(node = (t_list_token *)malloc(sizeof(t_list_token))))
		return(NULL);
	i++;
	while (str[i] && str[i] != '\'')
		i++;
    (str[i] == '\'') ? (node->is_ok = 1) : (node->is_ok = 0);
	node->type = QUOTE;
	node->data = ft_strsub(str, *index + 1, i - *index - 1);
	node->next = NULL;
	node->prec = NULL;
	(i + 1 < ft_strlen(str)) ? (*index = i + 1) : (*index = ft_strlen(str));
	return (node);
}

t_list_token	*add_dquote(int *index, char *str)
{
	t_list_token	*node;
	int i = *index;

	node = (t_list_token *)malloc(sizeof(t_list_token));
	if (!node)
		return (NULL);
	i++;
	while (str[i] && (str[i] != '"' || str[i - 1] == '\\'))
		i++;
    (str[i] == '"') ? (node->is_ok = 1) : (node->is_ok = 0);
	node->type = DQUOTE;
	node->data = (ft_strsub(str, *index + 1, i - *index - 1));
	if (is_dollar(node->data) >= 0)
		node->data = str_dollar_sub(node->data);
	node->next = NULL;
	node->prec = NULL;
    (i + 1 < ft_strlen(str)) ? (*index = i + 1) : (*index = ft_strlen(str));
	return (node);
}

t_list_token	*add_space(int *index, char *str)
{
	t_list_token	*node;
	int i = *index;

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
	node->data = ft_strsub(str, *index + 1, 1);
	node->next = NULL;
	node->prec = NULL;
	*index += 2;
	return (node);
}

t_list_token	*add_op(int *index, char *str, int op)
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

t_list_token	*add_word_int(int *index, char *str)
{
	int i;
	t_list_token	*node;

	i = *index;
	while (str[i] && is_op(str, i) == 0)
	{
		i++;
	}
	node = (t_list_token *)malloc(sizeof(t_list_token));
	if (!node)
		return (NULL);
	node->type = WORD;
	node->data = ft_strsub(str, *index, i - *index);
	node->next = NULL;
	node->prec = NULL;
	*index = i;
	return (node);
}

t_list_token	*tokenize(char *str, int *i)
{
	int op;
	t_list_token	*tmp;

	op = is_op(str, *i);
	if (op < 0)
	{
		if (op == QUOTE)
		{
			tmp = add_quote(i, str);
			return (tmp);
		}
		else if (op == DQUOTE)
		{
			tmp = add_dquote(i, str);
			return (tmp);
		}
		else if (op == SPACE)
		{
			tmp = add_space(i, str);
			return (tmp);
		}
		else if (op == ESCAPE)
		{
			tmp = add_escape(i, str);
			return (tmp);
		}
		else
		{
			tmp = add_op(i, str, op);
			return (tmp);
		}
	}
	else
	{
		tmp = add_word_int(i, str);
		return (tmp);
	}
}

t_list_token	*ft_tokenize(char *str)
{
	t_list_token	*head;
	t_list_token	*node;
	int i;

	head = NULL;
	i = 0;
	while(str[i])
	{
		if (!head)
		{
			head = tokenize(str, &i);
			head->prec = NULL;
			node = head;
		}
		else
		{
			node->next = tokenize(str, &i);
			node->next->prec = node;
			node = node->next;
		}
	}
	return (head);
}

int				is_valid_word(char *s)
{
	int	i;

	if (s[0] != '_' && !ft_isalpha(s[0]))
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != '_' && !ft_isalnum(s[i]))
			return(0);
		i++;
	}
	return (1);
}

int				is_all_digits(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int			is_valid_file(char *file, t_list_token *node)
{
	if (!node || !file)
		return (1);
	if (node->type <= -20 && node->type >= -31)
	{
		if (is_all_digits(file))
		{
			return (0);
		}
	}
	return (1);
}

char		*io_file(t_list_token **cmd, t_list_token **end, int *r_type)
{
	char	*file;

	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	if((*cmd)->type >= GRTAND && (*cmd)->type <= GRT)
	{
		*r_type = (*cmd)->type;
		*cmd = (*cmd)->next;
		while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
			*cmd = (*cmd)->next;;
		if (*cmd && ((*cmd)->type == WORD || (*cmd)->type == QUOTE || (*cmd)->type == DQUOTE))	// QOTE and DQOTE ??
		{
			if (is_valid_file((*cmd)->data, (*cmd)->next))
			{
				file = ft_strdup((*cmd)->data);
				if (*r_type == SMLAND && !is_all_digits(file) && ft_strcmp(file, "-"))
				{
					g_var.errno = 125;
					*cmd = NULL;
					ft_putstr_fd("expected file number, found: ", 2);
					ft_putstr_fd(file, 2);
					ft_putchar_fd('\n', 2);
					return (NULL);
				}
				*cmd = (*cmd)->next;
				return (file);
			}
			return ("");
		}
		ft_putstr_fd("syntax error, unexpected token near -- '", 2);
		if (*cmd)
		{
			ft_putstr_fd(tokentoa((*cmd)->type), 2);
		}
		else
		{
			ft_putstr_fd(tokentoa((*end)->type), 2);
		}
		ft_putstr_fd("'\n", 2);
		g_var.errno = 120;
		*cmd = NULL;
		return (NULL);
	}
	return (NULL);
}

char		*io_here(t_list_token **cmd, t_list_token **end, int *r_type)
{
	char	*file;
	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	if((*cmd)->type == SMLSML)
	{
		*r_type = (*cmd)->type;
		*cmd = (*cmd)->next;
		while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
			*cmd = (*cmd)->next;
		if (*cmd && ((*cmd)->type == WORD || (*cmd)->type == QUOTE || (*cmd)->type == DQUOTE))	// QOTE and DQOTE ??
		{
			if (is_valid_file((*cmd)->data, (*cmd)->next))
			{
				file = ft_strdup((*cmd)->data);
				*cmd = (*cmd)->next;
				return (file);
			}
			return ("");
		}
		ft_putstr_fd("syntax error, unexpected token near '", 2);
		if (*cmd)
		{
			ft_putstr_fd(tokentoa((*cmd)->type), 2);
		}
		else
		{
			ft_putstr_fd(tokentoa((*end)->type), 2);
		}
		ft_putstr_fd("'\n", 2);
		g_var.errno = 121;
		*cmd = NULL;
		return (NULL);
	}
	return (NULL);
}


t_io_redirect	*io_redirect(t_list_token **cmd, t_list_token **end)
{
	t_io_redirect	*io_r;
	t_list_token	*node;
	int				tmp;

	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	io_r = (t_io_redirect *)malloc(sizeof(t_io_redirect));
	io_r->io_num = -1;
	io_r->filename = io_file(cmd, end, &(io_r->redirect_type));
	if (io_r->filename)
	{
		return (io_r);
	}
	io_r->filename = io_here(cmd, end, &(io_r->redirect_type));
	if (io_r->filename)
	{
		return (io_r);
	}
	if (*cmd && (*cmd)->type == WORD && (*cmd)->next)
	{
		if (is_all_digits((*cmd)->data) && (*cmd)->next->type != SPACE)
		{
			node = *cmd;
			io_r->io_num = ft_atoi((*cmd)->data);
			*cmd = (*cmd)->next;
			if (!(*cmd))
			{
				*cmd = node;
				free(io_r);
				return (NULL);
			}
			io_r->filename = io_file(cmd, end, &(io_r->redirect_type));
			if (io_r->filename)
			{
				return (io_r);
			}
			io_r->filename = io_here(cmd, end, &(io_r->redirect_type));
			if (io_r->filename)
			{
				return (io_r);
			}
			if (g_var.errno)
			{
				free(io_r);
				return (NULL);
			}
			*cmd = node;
		}
	}
	free(io_r);
	return(NULL);
}

t_variable		*ass_word(t_list_token **cmd, t_list_token **end)
{
	t_variable	*var;
	int			i;

	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	if (*cmd && (*cmd)->type == WORD)
	{
		i = 1;
		while ((*cmd)->data[i])
		{
			if((*cmd)->data[i] == '=')
				break;
			i++;
		}
		if(i >= ft_strlen((*cmd)->data))
			return (NULL);
		var = (t_variable *)malloc(sizeof(t_variable));
		var->key = ft_strsub((*cmd)->data, 0, i);
		if (!is_valid_word(var->key))
		{
			ft_strdel(&(var->key));
			free(var);
			var = NULL;
			return (NULL);
		}
		var->value = ft_strdup(&((*cmd)->data[i + 1]));
		var->env = 1;
		*cmd = (*cmd)->next;
		return (var);
	}
	return (NULL);
}

t_cmd_prefix	*cmd_prefix(t_list_token **cmd, t_list_token **end)
{
	t_cmd_prefix	*node;

	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	node = (t_cmd_prefix *)malloc(sizeof(t_cmd_prefix));
	node->io_redirect = io_redirect(cmd, end);
	if (node->io_redirect)
	{
		node->ass_word = NULL;
		node->prefix = cmd_prefix(cmd, end);
		return (node);
	}
	node->ass_word = ass_word(cmd, end);
	if (node->ass_word)
	{
		node->io_redirect = NULL;
		node->prefix = cmd_prefix(cmd, end);
		return (node);
	}
	free(node);
	return (NULL);
}

char			*cmd_word(t_list_token **cmd, t_list_token **end)
{
	char	*word;

	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	if (((*cmd)->type == WORD || (*cmd)->type == QUOTE || (*cmd)->type == DQUOTE))
	{
		word = ft_strdup((*cmd)->data);
		*cmd = (*cmd)->next;
		return (word);
	}
	return (NULL);
}

t_cmd_suffix	*cmd_suffix(t_list_token **cmd, t_list_token **end)
{
	t_cmd_suffix	*node;

	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	node = (t_cmd_suffix *)malloc(sizeof(t_cmd_suffix));
	node->suffix = NULL;
	node->io_redirect = io_redirect(cmd, end);
	if (node->io_redirect)
	{
		node->word = NULL;
		node->suffix = cmd_suffix(cmd, end);
		return (node);
	}
	node->word = cmd_word(cmd, end);
	if (node->word)
	{
		node->io_redirect = NULL;
		node->suffix = cmd_suffix(cmd, end);
		return (node);
	}
	free_suffix(node);
	return (NULL);
}

char			*cmd_name(t_list_token	**cmd, t_list_token **end)
{
	char	*name;

	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	if (((*cmd)->type == WORD || (*cmd)->type == QUOTE || (*cmd)->type == DQUOTE))
	{
		name = ft_strdup((*cmd)->data);
		*cmd = (*cmd)->next;
		return (name);
	}
	return (NULL);
}

t_simple_cmd	*get_simple_cmd(t_list_token *start, t_list_token *end)
{
	t_simple_cmd *ret;

	if (g_var.errno)
		return (NULL);
	ret = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	ret->name = NULL;
	ret->word = NULL;
	ret->suffix = NULL;
	ret->prefix = cmd_prefix(&start, &end);
	if (ret->prefix)
	{
		ret->word = cmd_word(&start, &end);
		if (ret->word)
		{
			ret->suffix = cmd_suffix(&start, &end);
			return (ret);
		}
		return (ret);
	}
	else if ((ret->name = cmd_name(&start, &end)))
	{
		ret->suffix = cmd_suffix(&start, &end);
		return (ret);
	}
	else
	{
		if (!g_var.errno)
		{
			ft_putstr_fd("syntax error, unexpected token near '", 2);
			ft_putstr_fd(tokentoa(start->type), 2);
			ft_putstr_fd("'\n", 2);
			g_var.errno = 122;
		}
		return(NULL);
	}
}

t_pipe_seq	*ast(t_list_token *tokens)
{
	t_list_token	*node;
	t_list_token	*prec;
	t_pipe_seq		*tmp = NULL;

	if (!tokens || g_var.errno)
	{
		if (!g_var.errno)
		{
			ft_putstr_fd("syntax error, unexpected <newline>\n", 2);
			g_var.errno = 122;
		}
		return (NULL);
	}
	node = tokens;
	while (node)
	{
		if (node->type == PIP)
		{
			tmp = (t_pipe_seq *)malloc(sizeof(t_pipe_seq));
			tmp->left = get_simple_cmd(tokens, node);
			tmp->right = ast(node->next);
			return(tmp);
		}
		prec = node;
		node = node->next;
	}
	tmp = (t_pipe_seq *)malloc(sizeof(t_pipe_seq));
	tmp->left = get_simple_cmd(tokens, prec);
	tmp->right = NULL;
	return(tmp);
}

t_list_token	*list_sub(t_list_token *start, t_list_token *end)
{
	t_list_token *head = NULL;
	t_list_token *node;

	if (!start)
		return (NULL);
	while (start)
	{
		if (!head)
		{
			node = (t_list_token *)malloc(sizeof(t_list_token));
			node->prec = NULL;
			head = node;
		}
		else
		{
			node->next = (t_list_token *)malloc(sizeof(t_list_token));
			node->next->prec = node;
			node = node->next;
		}
		(start->data) ? (node->data = ft_strdup(start->data)) : (node->data = NULL);
		node->is_ok = start->is_ok;
		node->type = start->type;
		node->next = NULL;
		if (start == end)
			break;
		start = start->next;
	}
	return (head);
}

void	free_token_node(t_list_token **todel)
{
	ft_strdel(&((*todel)->data));
	free(*todel);
	*todel = NULL;
}

void	join_nodes(t_list_token *dst, t_list_token *todel)
{
	t_list_token	*node;
	char			*tmp;

	tmp = ft_strjoin(dst->data, todel->data);
	ft_strdel(&(dst->data));
	dst->data = tmp;
	dst->type = WORD;
	dst->next = todel->next;
	if (todel->next)
		todel->next->prec = dst;
	free_token_node(&todel);
}

void	join_words(t_list_token *token)
{
	t_list_token	*node;
	t_list_token	*tmp;

	node = token;
	while (node->next)
	{
		if (node->type == WORD || node->type == QUOTE || node->type == DQUOTE)
		{
			tmp = node->next;
			if (tmp->type == WORD || tmp->type == QUOTE || tmp->type == DQUOTE)
			{
				join_nodes(node, tmp);
				node = token;
			}
		}
		if (!(node->next))
			break;
		node = node->next;
	}
}

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
	if (ft_or(token->type, SMCLN, ANDLG, ORLG) || ft_or(token->type, PIP, BGJOB, 0))
		return (verify_tokens_error(2, node->type));
	node = token;
	while (node)
	{
		if (ft_or(token->type, SMCLN, ANDLG, ORLG) || token->type == BGJOB)
		{
			tmp = node->next;
			while(tmp && tmp->type == SPACE)
				tmp = tmp->next;
			if (!tmp && (node->type == ANDLG || node->type == ORLG))
				return (verify_tokens_error(3, node->type));
			if (tmp && (ft_or(token->type, SMCLN, ANDLG, ORLG) || token->type == BGJOB))
				return (verify_tokens_error(4, tmp->type));
		}
		node = node->next;
	}
	return (0);
}

t_and_or	*get_andor_list(t_list_token *strt, int dep, t_list_token *end)
{
	t_and_or		*node;
	t_list_token	*tmp;

	if (!strt)
		return (NULL);
	if (!(node = (t_and_or *)malloc(sizeof(t_and_or))))
		return (NULL);
	node->next = NULL;
	tmp = list_sub(strt, end);
	node->ast = ast(tmp);
	free_tokens(tmp);
	if (!(node->ast))
		return (NULL);
	node->dependent = 0;
	if (dep == ANDLG)
		node->dependent = 1;
	if (dep == ORLG)
		node->dependent = 2;
	return (node);
}

t_and_or	*token_split_andor(t_list_token *start, t_list_token *end, int bg)
{
	t_and_or		*list;
	t_and_or		*node;
	t_list_token	*tmp;

	if (!start || g_var.errno)
		return (NULL);
	tmp = start;
	list = NULL;
	while (tmp && tmp != end)
	{
		if (tmp->type == ORLG || tmp->type == ANDLG)
		{
			if (!list)
			{
				node = get_andor_list(start, 0, tmp->prec);
				list = node;
			}
			else
			{
				node->next = get_andor_list(start->next, start->type, tmp->prec);
				node = node->next;
			}
			start = tmp;
		}
		tmp = tmp->next;
	}
	if (!list)
	{
		list = get_andor_list(start, 0, end);
	}
	else
	{
		node->next = get_andor_list(start->next, start->type, end);
	}
	return (list);
}

t_cmdlist	*token_split_sep_op(t_list_token *tokens)
{
	t_cmdlist		*list;
	t_cmdlist		*node;
	t_list_token	*tmp;

	if (!tokens || g_var.errno)
		return (NULL);
	tmp = tokens;
	list = NULL;
	while (tmp)
	{
		if (tmp->type == SMCLN || tmp->type ==BGJOB)
		{
			if (!list)
			{
				node = (t_cmdlist *)malloc(sizeof(t_cmdlist));
				node->and_or = token_split_andor(tokens, tmp->prec, tmp->type);
				list = node;
			}
			else
			{
				node->next = (t_cmdlist *)malloc(sizeof(t_cmdlist));
				node = node->next;
				node->and_or = token_split_andor(tokens->next, tmp->prec, tmp->type);
			}
			(tmp->type == BGJOB) ? (node->bg = 1) : (node->bg = 0);
			tokens = tmp;
			node->next = NULL;
		}
		tmp = tmp->next;
	}
	if (!list)
	{
		list = (t_cmdlist *)malloc(sizeof(t_cmdlist));
		list->and_or = token_split_andor(tokens, NULL, SMCLN);
		list->bg = 0;
		list->next = NULL;
	}
	else if (tokens->next)
	{

		node->next = (t_cmdlist *)malloc(sizeof(t_cmdlist));
		node = node->next;
		node->and_or = token_split_andor(tokens->next, NULL, SMCLN);
		node->bg = 0;
		node->next = NULL;
	}
	return (list);
}

int		need_append(t_list_token *tokens)
{
	t_list_token	*node;
	t_list_token	*ttt;
	char			*toappend;
	char			*tmp;
	int				typ;

	node = tokens;
	while (node->next)
		node = node->next;
	while (node && node->type == SPACE)
		node = node->prec;
	typ = node->type;
	if (typ == PIP || typ == ESCAPE || ((typ == QUOTE || typ == DQUOTE) && node->is_ok == 0))
	{
		tmp = readline(typ);
		if (!ft_strcmp(tmp, "\030") || !ft_strcmp(tmp, "\033"))
			return (1);
		if (typ == QUOTE || typ == DQUOTE)
		{
			toappend = ft_strjoin(node->data, "\n");
			toappend = ft_strjoin(toappend, tmp);
			toappend = ft_strjoin(tokentoa(typ), toappend);
			ttt = ft_tokenize(toappend);
			if (ttt->next)
				ttt->next->prec = node;
			node->data = ttt->data;
			node->type = ttt->type;
			node->is_ok = ttt->is_ok;
			node->next = ttt->next;
		}
		else
		{
			toappend = tmp;
			node->next = ft_tokenize(toappend);
		}
		ft_strdel(&toappend);
		if (lexer(&tokens) || verify_tokens(tokens))
		{
			return (100);
		}
		return (need_append(tokens));
	}
	return (0);
}

char		*here_doc_string(char *word)
{
	char	*str;
	char	*tmp;
	char	*buff;

	str = ft_strdup("");
	while (1)
	{
		buff = readline(SMLSML);
		if (!ft_strcmp(buff, "\033"))
		{
			g_var.errno = 1;
			ft_strdel(&buff);
			ft_strdel(&str);
			return (ft_strdup(""));
		}
		if (!ft_strcmp(buff, "\030"))
		{
			ft_strdel(&buff);
			return (str);
		}
		if (!ft_strcmp(buff, word))
		{
			ft_strdel(&buff);
			return (str);
		}
		tmp = ft_strjoin(str, buff);
		ft_strdel(&str);
		str = ft_strjoin(tmp, "\n");
		ft_strdel(&tmp);
		ft_strdel(&buff);
	}
	return (NULL);
}

void	here_doc(t_list_token *head)
{
	t_list_token	*node;
	char			*str;

	node = head;
	while (node)
	{
		if (node->type == SMLSML)
		{
			while (node->next && node->next->type == SPACE)
				node = node->next;
			if (!node->next)
				return;
			if (node->next->type == WORD)
			{
				str = str_dollar_sub(here_doc_string(node->next->data));
			}
			else if (node->next->type == QUOTE|| node->next->type == DQUOTE)
			{
				str = here_doc_string(node->next->data);
			}
			ft_strdel(&(node->next->data));
			node->next->data = str;
			node->next->type = QUOTE;
			node->next->is_ok = 1;
		}
		node = node->next;
	}
}

char			*last_in_hist(void)
{
	t_hist	*node;

	node = g_var.history;
	while (node->next)
		node = node->next;
	if (node)
	{
		return (ft_strdup(node->hist_str));
	}
	return (NULL);

}

void			add_proc(pid_t pid)
{
	t_proc	*node;

	node = g_var.proc;
	while (node->next)
		node = node->next;
	node->next = (t_proc *)malloc(sizeof(t_proc));
	node->next->ppid = pid;
	node->next->index = node->index + 1;
	node->next->done = 0;
	node->next->status = -1;
	node->next->str = last_in_hist();
	node->next->next = NULL;
	ft_putstr("[");
	ft_putnbr(node->next->index);
	ft_putstr("] ");
	ft_putnbr(pid);
	ft_putstr("\n");
}

void	delet_proc(pid_t pid)
{
	t_proc	*node;
	t_proc	*old_node;

	node = g_var.proc;
	old_node = NULL;
	while (node)
	{
		if (pid == node->ppid)
		{
			ft_strdel(&(node->str));
			old_node->next = node->next;
			free(node);
			break;
		}
		old_node = node;
		node = node->next;
	}
}

void	bg_jobs(void)
{
	t_proc	*proc;

	proc = g_var.proc;
	while (proc)
	{
		if (proc->done == 1)
		{
			ft_print(STDOUT, "\n[%d]\tDone\t\t%s\n",proc->index, proc->str);
			delet_proc(proc->ppid);
		}
		proc = proc->next;
	}
}

int		manage_cmd_list(t_cmdlist *cmdlist)
{
	t_cmdlist		*node;
	int				ret;

	node = cmdlist;
	ret = 0;
	while (node)
	{
		ret = execute(node->and_or, node->bg);
		node = node->next;
	}
	free_cmd_list(cmdlist);
	return (ret);
}

int 	main_parse(char *line)
{
	t_list_token    *tokens;
	t_cmdlist		*cmdlist;
	int				ret;

    tokens = ft_tokenize(line);
	g_var.errno = 0;
	if (lexer(&tokens) || verify_tokens(tokens))
	{
		return (100);
	}
	if (need_append(tokens))
		return (100);
	join_words(tokens);
	here_doc(tokens);
	cmdlist = token_split_sep_op(tokens);
	free_tokens(tokens);
	if (!cmdlist || g_var.errno)
		return (42);
	return (manage_cmd_list(cmdlist));
}
