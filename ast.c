/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:35:31 by afaraji           #+#    #+#             */
/*   Updated: 2020/02/14 22:35:36 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "readline.h"
#include "lexer.c"
#include "exec.c"

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
	if (str[i] == '&' && str[i + 1] == '&')	// should escape 2nd &
		return (ANDLG);
	if (str[i] == '|' && str[i + 1] == '|')	// should escape 2nd |
		return (ORLG);
	if (str[i] == '|')
		return (PIP);
	if (str[i] == 92)
		return (ESCAPE);
	// if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '-')
	// 	return (DSMLDASH);
	if ((str[i] == '>' && str[i + 1] == '&') || (str[i] == '&' && str[i + 1] == '>'))
		return (GRTAND);
	// if (str[i] == '>' && str[i + 1] == '|')
	// 	return (CLOBBER);
	if (str[i] == '>' && str[i + 1] == '>')	// should escape 2nd >
		return (GRTGRT);
	if ((str[i] == '<' && str[i + 1] == '&'))// || (str[i] == '&' && str[i + 1] == '<'))
		return (SMLAND);
	// if (str[i] == '<' && str[i + 1] == '>')
	// 	return (SMLGRT);
	if (str[i] == '<' && str[i + 1] == '<')	// should escape 2nd <
		return (SMLSML);
	if (str[i] == '>')
		return (GRT);
	if (str[i] == '<')
		return (SML);
	if (str[i] == '&')
		return (BGJOB);
	return (0);
}

void	token_print(t_list_token *node)
{
	fprintf(ttyfd, "\n");
	while (node)
	{
		if(node->type == WORD)
			fprintf(ttyfd, "[%s:%d]", node->data, node->type);
		else if(node->type == QUOTE || node->type == DQUOTE)
			fprintf(ttyfd, "{%d:%s}", node->is_ok, node->data);
		else
		{
			//fprintf(ttyfd, "(%d)", node->type);
			switch (node->type)
			{
			case -1:
				fprintf(ttyfd, "_");
				break;
			case -4:
				fprintf(ttyfd, ";");
				break;
			case -5:
				fprintf(ttyfd, "(&&)");
				break;
			case -6:
				fprintf(ttyfd, "||");
				break;
			case -10:
				fprintf(ttyfd, "|");
				break;
			case -11:
				fprintf(ttyfd, "&");
				break;
			case -12:
				fprintf(ttyfd, "[%s:%d]", node->data, node->type);
				break;
			case -20:
				fprintf(ttyfd, ">");
				break;
			case -21:
				fprintf(ttyfd, ">>");
				break;
			case -22:
				fprintf(ttyfd, "<");
				break;
			case -30:
				fprintf(ttyfd, "<<");
				break;
			
			default:
				fprintf(ttyfd, "[%d]", node->type);
				break;
			}
		}
		node = node->next;
	}
	fprintf(ttyfd, "\n");
}

void	token_print_inverse(t_list_token *node)
{
	fprintf(ttyfd, "\n");
	while (node->next)
		node = node->next;
	
	while (node)
	{
		if(node->type == WORD)
			fprintf(ttyfd, "[%s]", node->data);
		else if(node->type == QUOTE || node->type == DQUOTE)
			fprintf(ttyfd, "{%d:%s}", node->is_ok, node->data);
		else
		{
			//fprintf(ttyfd, "(%d)", node->type);
			switch (node->type)
			{
			case -1:
				fprintf(ttyfd, "_");
				break;
			case -4:
				fprintf(ttyfd, ";");
				break;
			case -5:
				fprintf(ttyfd, "(&&)");
				break;
			case -6:
				fprintf(ttyfd, "||");
				break;
			case -10:
				fprintf(ttyfd, "|");
				break;
			case -11:
				fprintf(ttyfd, "&");
				break;
			case -12:
				fprintf(ttyfd, "[%s]", node->data);
				break;
			case -20:
				fprintf(ttyfd, ">");
				break;
			case -21:
				fprintf(ttyfd, ">>");
				break;
			case -22:
				fprintf(ttyfd, "<");
				break;
			case -30:
				fprintf(ttyfd, "<<");
				break;
			
			default:
				fprintf(ttyfd, "[%d]", node->type);
				break;
			}
		}
		node = node->prec;
	}
	fprintf(ttyfd, "\n");
}

char	*tokentoa(int token)
{
	
	switch (token)
	{
		case -1:
			return(" ");
			break;
		case -2:
			return("'");
			break;
		case -3:
			return("\"");
			break;
		case -4:
			return(";");
			break;
		case -5:
			return("&&");
			break;
		case -6:
			return("||");
			break;
		case -10:
			return("|");
			break;
		case -11:
			return("&");
			break;
		case -12:
			return("\\");
			break;
		case -20:
			return(">");
			break;
		case -21:
			return(">>");
			break;
		case -22:
			return("<");
			break;
		case -30:
			return("<<");
			break;
		case -24:
			return("<&");
			break;
		case -25:
			return(">&");
			break;
		case -26:
			return("<>");
			break;
		case -27:
			return(">|");
			break;
		case -31:
			return("<<-");
			break;
		
		default:
			return(ft_itoa(token));
			break;
	}
		
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
	node->data = ft_strsub(str, *index + 1, i - *index - 1); // i = 0; or i = *index ?
	node->next = NULL;
	node->prec = NULL;
	(i + 1 < ft_strlen(str)) ? (*index = i + 1) : (*index = ft_strlen(str));
	return (node);
}

t_list_token	*add_dquote(int *index, char *str)		// backslash and dollar exeption
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
	node->data = (ft_strsub(str, *index + 1, i - *index - 1));		// i = 0; or i = *index ?
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

	node = (t_list_token *)malloc(sizeof(t_list_token));	//need protection if malloc fails.
	node->type = SPACE;
	node->data = NULL;
	node->next = NULL;
	node->prec = NULL;
	while (ft_isspace(str[i]))
		i++;
	*index = i;
	return (node);
}

t_list_token	*add_escape(int *index, char *str) // need thinking and recoding
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

t_list_token	*__tokenize(char *str)
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

//*********** tmp print ************

void	print_io_redirect(t_io_redirect *head)
{
	t_io_redirect *node;

	fprintf(ttyfd,"IO_redirect: ");
	if (!head)
		return;
	node = head;
	fprintf(ttyfd,"[type:%s|%d|%s]\n", tokentoa(node->redirect_type), node->io_num, node->filename);
}

void	print_cmdprefix(t_cmd_prefix *head)
{
	t_cmd_prefix *node;

	fprintf(ttyfd,"------- prefix: ------\n");
	if (!head)
		return;
	node = head;
	if (node->io_redirect)
		print_io_redirect(head->io_redirect);
	if (node->ass_word)
		fprintf(ttyfd, "assWord [env = %d, %s=%s]\n", node->ass_word->env, node->ass_word->key, node->ass_word->value);
	if (node->prefix)
		print_cmdprefix(node->prefix);
}

void	print_cmdsuffix(t_cmd_suffix *head)
{
	if (!head)
		return;
	fprintf(ttyfd,"------- suffix: ------\n");
	if (head->io_redirect)
	{
		print_io_redirect(head->io_redirect);
	}
	if (head->word)
	{
		fprintf(ttyfd, "WORD:[%s]\n", head->word);
	}
	if (head->suffix)
		print_cmdsuffix(head->suffix);
	
}

void	print_simple_cmd(t_simple_cmd *cmd)
{
	if (!cmd)
		return;
	if (cmd->prefix)
	{
		print_cmdprefix(cmd->prefix);
		fprintf(ttyfd,"cmdWord ==>[%s]\n", cmd->word);
		print_cmdsuffix(cmd->suffix);
	}
	else if (cmd->name)
	{
		fprintf(ttyfd,"cmdName ==>[%s]\n", cmd->name);
		print_cmdsuffix(cmd->suffix);
	}
	else
	{
		fprintf(ttyfd,"naaaaaaaaaaaaaallllll\n");
	}
	
}

//**********************************

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
				if (*r_type == SMLAND && !is_all_digits(file))
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
	if((*cmd)->type == SMLSML)// || (*cmd)->type == DSMLDASH)
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
	if (*cmd && (*cmd)->type == WORD)
	{
		if (is_all_digits((*cmd)->data))
		{
			node = *cmd;
			io_r->io_num = ft_atoi((*cmd)->data);
			*cmd = (*cmd)->next;
			if (!(*cmd))
			{
				*cmd = node;
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
				return (NULL);
			*cmd = node;
		}
	}
	//free(io_r);
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
			free(var->key);
			free(var);
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
	//free(node);
	return (NULL);
}

char			*cmd_word(t_list_token **cmd, t_list_token **end) // need to apply rule 7b ? and need to include qote and dqote(is_ok = ?)
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
	// what if type is quote o dquote ?
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
	
	//free(node);
	return (NULL);
}

char			*cmd_name(t_list_token	**cmd, t_list_token **end)	// need to apply rule 7a ? and need to include qote and dqote(is_ok = ?)
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

t_simple_cmd	*get_simple_cmd(t_list_token *start, t_list_token *end) // need recoding and rethinking
{
	t_simple_cmd *ret;

	if (g_var.errno)
		return (NULL);
	ret = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	ret->prefix = cmd_prefix(&start, &end);
	if (ret->prefix)
	{
		ret->word = cmd_word(&start, &end);					//	include " '
		if (ret->word)
		{
			ret->suffix = cmd_suffix(&start, &end);			//	include " '
			return (ret);
		}
		return (ret);
	}
	else if ((ret->name = cmd_name(&start, &end)))			//	include " '
	{
		ret->suffix = cmd_suffix(&start, &end);				//	include " '
		return (ret);
	}
	else
	{
		if (!g_var.errno)// here if sigfaults
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

void	print_tokenlist(t_pipe_seq *ast)
{
	t_simple_cmd	*node;

	if (!ast)
		return;
	node = ast->left;
	print_simple_cmd(node);
	print_tokenlist(ast->right);	
}

void	print_andor(t_cmdlist *list)
{
	t_and_or	*node;

	node = list->and_or;
	while (node)
	{
		fprintf(ttyfd,"+-+-+-+-+-+-+-+-+-+-+---+-+\ndependent ===>[%d]\n", node->dependent);
		print_tokenlist(node->ast);
		node = node->next;
	}
	
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
	free(dst->data);
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
		fprintf(ttyfd,"====[%d:%s]===\n", node->type, node->data);
		if (node->type == WORD || node->type == QUOTE || node->type == DQUOTE)
		{
			tmp = node->next;
			if (tmp->type == WORD || tmp->type == QUOTE || tmp->type == DQUOTE)
			{
				fprintf(ttyfd,"joining [%s]-[%s]\n", node->data, tmp->data);
				join_nodes(node, tmp);
				node = token;
				// continue;
			}
		}
		if (!(node->next))
			break;
		node = node->next;
	}
}

int		verify_tokens(t_list_token *token)
{
	t_list_token	*node;
	t_list_token	*tmp;

	if (!token)
		return (1);
	if (_OR(token->type, SMCLN, ANDLG, ORLG, BGJOB, PIP))
	{
		ft_putstr_fd("syntax error, unexpected token `", 2);
		ft_putstr_fd(tokentoa(token->type), 2);
		ft_putstr_fd("'\n", 2);
		g_var.errno = 130;
		return (2);
	}
	node = token;
	while (node)
	{
		if (_OR(node->type, SMCLN, ANDLG, ORLG, BGJOB, SMCLN))
		{
			tmp = node->next;
			while(tmp && tmp->type == SPACE)
				tmp = tmp->next;
			if (!tmp && (node->type == ANDLG || node->type == ORLG))
			{
				ft_putstr_fd("syntax error after `", 2);
				ft_putstr_fd(tokentoa(node->type), 2);
				ft_putstr_fd("'\n", 2);
				g_var.errno = 131;
				return (3);
			}
			if (tmp && (_OR(tmp->type, SMCLN, ANDLG, ORLG, BGJOB, SMCLN)))
			{
				ft_putstr_fd("syntax error, unexpected token `", 2);
				ft_putstr_fd(tokentoa(tmp->type), 2);
				ft_putstr_fd("'\n", 2);
				g_var.errno = 132;
				return (4);
			}
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
	// free(tmp);
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
		if (typ == QUOTE || typ == DQUOTE)
		{
			toappend = ft_strjoin(node->data, "\n");
			toappend = ft_strjoin(toappend, readline(typ));
			toappend = ft_strjoin(tokentoa(typ), toappend);
			ttt = __tokenize(toappend);
			token_print(ttt);
			if (ttt->next)
				ttt->next->prec = node;
			node->data = ttt->data;
			node->type = ttt->type;
			node->is_ok = ttt->is_ok;
			node->next = ttt->next;
		}
		else
		{
			toappend = readline(typ);
			node->next = __tokenize(toappend);
		}
		free(toappend);
		if (lexer(&tokens) || verify_tokens(tokens))
		{
			return (100);
		}
		return (need_append(tokens));
	}
	return (0);
}

int main_parse(char *line)
{
	t_list_token    *tokens;
	t_cmdlist		*cmdlist = NULL;
	t_cmdlist		*node;
	int				ret;

    tokens = __tokenize(line);
	// fprintf(ttyfd,"----*+*1+*+---------\n");
	// token_print(tokens);
	// fprintf(ttyfd,"----*+*+*1+*+*+---------\n");
	
	g_var.errno = 0;
	if (lexer(&tokens) || verify_tokens(tokens))
	{
		return (100);
	}
	if (need_append(tokens))
		return (100);
	join_words(tokens);
	cmdlist = token_split_sep_op(tokens);
	if (!cmdlist || g_var.errno)
		return (42);
	// free_tokens(tokens);
	node = cmdlist;
	while (node)
	{
		// print_andor(node);
		ret = execute(node->and_or, node->bg);
		// print_tokenlist(node->and_or->ast);
		node = node->next;
	}
	return (0);
}

// correct error management with (g_var.[errno, err_str])
// escape deep thinking and search
