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
	if (str[i] == '&')
		return (BGJOB);
	if (str[i] == 92)
		return (ESCAPE);
	if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '-')
		return (DSMLDASH);
	if (str[i] == '>' && str[i + 1] == '&')
		return (GRTAND);
	if (str[i] == '>' && str[i + 1] == '|')
		return (CLOBBER);
	if (str[i] == '>' && str[i + 1] == '>')	// should escape 2nd >
		return (GRTGRT);
	if (str[i] == '<' && str[i + 1] == '&')
		return (SMLAND);
	if (str[i] == '<' && str[i + 1] == '>')
		return (SMLGRT);
	if (str[i] == '<' && str[i + 1] == '<')	// should escape 2nd <
		return (SMLSML);
	if (str[i] == '>')
		return (GRT);
	if (str[i] == '<')
		return (SMLSML);
	return (0);
}

void	token_print(t_list_token *node)
{
	while (node)
	{
		if(node->type == WORD)
			printf("%s", node->data);
		else if(node->type == QUOTE || node->type == DQUOTE)
			printf("{%d:%s}", node->is_ok, node->data);
		else
		{
			//printf("(%d)", node->type);
			switch (node->type)
			{
			case -1:
				printf("_");
				break;
			case -4:
				printf(";");
				break;
			case -5:
				printf("&&");
				break;
			case -6:
				printf("||");
				break;
			case -10:
				printf("|");
				break;
			case -11:
				printf("&");
				break;
			case -12:
				printf("[%s]", node->data);
				break;
			case -20:
				printf(">");
				break;
			case -21:
				printf(">>");
				break;
			case -22:
				printf("<");
				break;
			case -23:
				printf("<<");
				break;
			
			default:
				printf("[%d]", node->type);
				break;
			}
		}
		node = node->next;
	}
	//printf("\n");
}

t_list_token	*remove_space(t_list_token *oldcmd)
{
	t_list_token *node;
	t_list_token *tmp;

	node = oldcmd;
	while (node)
	{
		if (node->type == SPACE)
		{
			tmp = node;
			if (node->next)
				node->prec->next = node->next;
			else
				node->prec->next = NULL;
			if (node->prec)
			{
				node->next->prec = node->prec;
				node = node->prec;
			}
			else
			{
				node->next->prec = NULL;
				oldcmd = node->next;
				node = oldcmd;
				// free_node(tmp);
				continue;
			}
			//free_node(tmp);
		}
		node = node->next;
	}
	return (oldcmd);
}

void	print_ast(t_pipe_seq *cmd)
{
	while(cmd)
	{
		printf("cmd[");
		token_print(cmd->left->tokens);
		
		if (cmd->right)
		{
			printf("] --PIPE--> ");
			printf("cmd[");
			token_print(cmd->right->left->tokens);
			printf("]\n");
		}
		else
		{
			printf("] ----> ");
			printf("standard output");
		}
		cmd = cmd->right;
	}
}

t_list_token	*add_quote(int *index, char *str)
{
	t_list_token	*node;
	int i = *index;

	node = (t_list_token *)malloc(sizeof(t_list_token));	//need protection if malloc fails.
	i++;
	while (str[i] && str[i] != 39)
		i++;
    (str[i] == 39) ? (node->is_ok = 1) : (node->is_ok = 0);
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

	node = (t_list_token *)malloc(sizeof(t_list_token));	//need protection if malloc fails.
	i++;
	while (str[i] && str[i] != 34 && str[i - 1] != 92)		// need testing
		i++;
    (str[i] == 34) ? (node->is_ok = 1) : (node->is_ok = 0);
	node->type = DQUOTE;
	node->data = ft_strsub(str, *index + 1, i - *index - 1);		// i = 0; or i = *index ?
	node->next = NULL;
	node->prec = NULL;
    (i + 1 < ft_strlen(str)) ? (*index = i + 1) : (*index = ft_strlen(str));
	*index = i + 1;
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

	node = (t_list_token *)malloc(sizeof(t_list_token));	//need protection if malloc fails.
	node->type = ESCAPE;
	// need to verifie if it s a reserved word
	node->data = ft_strsub(str, *index + 1, 1);printf("---|%s|---\n", node->data);
	node->next = NULL;
	node->prec = NULL;
	*index += 2;
	return (node);
}

t_list_token	*add_op(int *index, char *str, int op)
{
	t_list_token	*node;

	node = (t_list_token *)malloc(sizeof(t_list_token));	//need protection if malloc fails.
	if (op == ANDLG || op == ORLG || op == GRTGRT || op == SMLSML)
		*index += 1;
	if (op == SMLAND || op == GRTAND || op == SMLGRT || op == CLOBBER)
		*index += 1;
	if (op == DSMLDASH)
		*index += 2;
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
	node = (t_list_token *)malloc(sizeof(t_list_token));	//need protection if malloc fails.
	node->type = WORD;
	node->data = ft_strsub(str, *index, i - *index); // i = 0; or i = *index ?
	node->next = NULL;
	node->prec = NULL;
	*index = i;
	return (node);
}

t_list_token	*tokenize(char *str, int *i)
{
	int op;
	t_list_token	*tmp;

	if ((op = is_op(str, *i)) < 0)
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

char		*io_file(t_list_token **cmd, int *r_type)
{
	char	*file;

	if((*cmd)->type >= CLOBBER && (*cmd)->type <= GRT)
	{
		*r_type = (*cmd)->type;
		fprintf(ttyfd, "******[%d:%s]\n", (*cmd)->type, (*cmd)->data); 
		*cmd = (*cmd)->next;
		while ((*cmd)->type == SPACE)
			*cmd = (*cmd)->next;
		if ((*cmd)->type == WORD)	// QOTE and DQOTE ??
		{
			file = ft_strdup((*cmd)->data);
			fprintf(ttyfd, "******[%d:%s]\n", (*cmd)->type, (*cmd)->data);
			*cmd = (*cmd)->next;
			return (file);
		}
		printf("syntax error, unexpected token near %d\n", *r_type);
	}
	return (NULL);
}

char		*io_here(t_list_token **cmd, int *r_type)
{
	char	*file;

	if((*cmd)->type == SMLSML || (*cmd)->type == DSMLDASH)
	{
		*r_type = (*cmd)->type;
		fprintf(ttyfd, "******[%d:%s]\n", (*cmd)->type, (*cmd)->data);
		*cmd = (*cmd)->next;
		while ((*cmd)->type == SPACE)
			*cmd = (*cmd)->next;
		if ((*cmd)->type == WORD)	// QOTE and DQOTE ??
		{
			file = ft_strdup((*cmd)->data);
			fprintf(ttyfd, "******[%d:%s]\n", (*cmd)->type, (*cmd)->data);
			*cmd = (*cmd)->next;
			return (file);
		}
		printf("syntax error, unexpected token near %d\n", *r_type);
	}
	return (NULL);
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

t_io_redirect	*io_redirect(t_list_token **cmd)
{
	t_io_redirect	*io_r;
	int				tmp;
	
	while ((*cmd)->type == SPACE)
		*cmd = (*cmd)->next;
	fprintf(ttyfd, "++++++++++++++ io_redirect +++++++++++++++[%d:%s]\n", (*cmd)->type, (*cmd)->data);
	io_r = (t_io_redirect *)malloc(sizeof(t_io_redirect));
	io_r->filename = io_file(cmd, &(io_r->redirect_type));

	if (io_r->filename)
	{
		fprintf(ttyfd, "-----1------ io_redirect returned value: [%d:%s]\n", io_r->redirect_type, io_r->filename);
		return (io_r);
	}
	io_r->filename = io_here(cmd, &(io_r->redirect_type));
	if (io_r->filename)
	{
		fprintf(ttyfd, "-----2------ io_redirect returned value\n");
		return (io_r);
	}
	if ((*cmd)->type == WORD)
	{
		if (is_all_digits((*cmd)->data))
		{
			io_r->io_num = ft_atoi((*cmd)->data);
			fprintf(ttyfd, "******[%d:%s]\n", (*cmd)->type, (*cmd)->data);
			*cmd = (*cmd)->next;
			io_r->filename = io_file(cmd, &(io_r->redirect_type));
			if (io_r->filename)
			{
				fprintf(ttyfd, "-----3------ io_redirect returned value\n");
				return (io_r);
			}
			io_r->filename = io_here(cmd, &(io_r->redirect_type));
			if (io_r->filename)
			{
				fprintf(ttyfd, "-----4------ io_redirect returned value\n");
				return (io_r);
			}
			*cmd = (*cmd)->prec;
		}
	}
	free(io_r);
	return(NULL);
}

t_variable		*ass_word(t_list_token **cmd)
{
	t_variable	*var;
	int			i;

	while ((*cmd)->type == SPACE)
		*cmd = (*cmd)->next;
	fprintf(ttyfd, "++++++++++++++ ass_word +++++++++++++++[%d:%s]\n", (*cmd)->type, (*cmd)->data);
	if ((*cmd)->type == WORD)
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
			free(var->value);
			free(var->key);
			free(var);
			return (NULL);
		}
		var->value = ft_strdup(&((*cmd)->data[i + 1]));
		var->env = 1;
		fprintf(ttyfd, "******[%d:%s]\n", (*cmd)->type, (*cmd)->data);
		*cmd = (*cmd)->next;
		return (var);
	}
	return (NULL);
}

t_cmd_prefix	*cmd_prefix(t_list_token **cmd)
{
	t_cmd_prefix	*node;

	if (!cmd || !(*cmd))
		return (NULL);
	printf("head(%p):", *cmd);token_print(*cmd);
	fprintf(ttyfd, "++++(%p)+++++++++ cmd_prefix +++++++++++++++[%d:%s]\n", *cmd,(*cmd)->type, (*cmd)->data);
	node = (t_cmd_prefix *)malloc(sizeof(t_cmd_prefix));
	node->io_redirect = io_redirect(cmd);
	if (node->io_redirect)
	{
		node->ass_word = NULL;
		// why cmd's value segfaults
		fprintf(ttyfd, "----0------- cmd_prefix [%d:%s]\n", (*cmd)->type, (*cmd)->data);
		fprintf(ttyfd, "44******[%d:%s] --> %p \n", (*cmd)->type, (*cmd)->data, (*cmd)->next);
		*cmd = (*cmd)->next;// ?? why it's 0x00
		fprintf(ttyfd, "55******[%d:%s]\n", (*cmd)->type, (*cmd)->data);
		node->prefix = cmd_prefix(cmd);
		fprintf(ttyfd, "----1------- cmd_prefix returned value --[%d:%s]\n", (*cmd)->type, (*cmd)->data);
		return (node);
	}
	node->ass_word = ass_word(cmd);
	if (node->ass_word)
	{
		node->io_redirect = NULL;
		fprintf(ttyfd, "******[%d:%s]\n", (*cmd)->type, (*cmd)->data);
		*cmd = (*cmd)->next;
		node->prefix = cmd_prefix(cmd);
		fprintf(ttyfd, "-----2------ cmd_prefix returned value\n");
		return (node);
	}
	fprintf(ttyfd, "-----9------ cmd_prefix NULL returned\n");
	free(node);
	return (NULL);
}

char			*cmd_word(t_list_token **cmd)
{
	char	*word;
	fprintf(ttyfd, "-----SSS------ cmd_word ==> [%d:%s]\n",(*cmd)->type, (*cmd)->data);
	while ((*cmd)->type == SPACE)
		*cmd = (*cmd)->next;
	fprintf(ttyfd, "-----0------ cmd_word\n");
	if ((*cmd)->type == WORD)
	{
		word = ft_strdup((*cmd)->data);
		fprintf(ttyfd, "******[%d:%s]\n", (*cmd)->type, (*cmd)->data);
		*cmd = (*cmd)->next;
		return (word);
	}
	// what if type is quote o dquote ?
	return (NULL);
}

t_cmd_suffix	*cmd_suffix()
{
	return (NULL);
}

char			*cmd_name(t_list_token	**cmd)
{
	return (NULL);
}

//*********** tmp print ************

void	print_cmdprefix(t_cmd_prefix *head)
{
	t_cmd_prefix *node;
	int i = 0;

	fprintf(ttyfd, "******************************\n");
	if (!head)
	{
		fprintf(ttyfd, "no cmdPrefix\n");
		return;
	}
	node = head;
	while (node)
	{
		fprintf(ttyfd, "----------- NODE (%d) -----------\n", i);
		if (node->ass_word)
		{
			t_variable *tmp;
			tmp = node->ass_word;
			fprintf(ttyfd, "=======> ass_word = [%d:%s:%s]\n", tmp->env,tmp->key,tmp->value);
		}
		if (node->io_redirect)
		{
			t_io_redirect *tmp;
			tmp = node->io_redirect;
			fprintf(ttyfd, "=======> io_redrct = [%d:%d:%s]\n", tmp->redirect_type,tmp->io_num,tmp->filename);
		}
		node = node->prefix; i++;
	}
	fprintf(ttyfd, "-------------------------------\n");
}

//**********************************

t_simple_cmd	*get_simple_cmd(t_list_token *cmd) // need recoding and rethinking
{
	char *cmdWord;
	t_simple_cmd *ret;

	ret = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	while (cmd->type == SPACE)
		cmd = cmd->next;
	ret->prefix = cmd_prefix(&cmd);
	if (ret->prefix)
	{
		fprintf(ttyfd, "====== %p =======\n", cmd);
		fprintf(ttyfd, "-----A------>[%d:%s] \n", cmd->type, cmd->data);
		ret->word = cmd_word(&cmd);fprintf(ttyfd, "-----B------ \n");
		if (ret->word)
		{
			print_cmdprefix(ret->prefix);
			return (NULL); // tmp for testing (dont want it to continue cause word, name and suffix always NULL)
			ret->suffix = cmd_suffix();
			return (ret);
		}
		return (ret);
	}
	else if ((ret->name = cmd_name(&cmd)))
	{
		ret->suffix = cmd_suffix();
		return (ret);
	}
	else
	{
		fprintf(ttyfd, "getSimpleCmd: syntax error near unexpected token %s\n", cmd->data);
		return(NULL);
	}
}

t_comp_cmd	*get_comp_cmd(t_list_token *pipe)
{
	t_list_token	*node;
	t_comp_cmd		*ret;

	node = pipe;
	pipe->prec = NULL;
	while (node->next && node->next->type != PIP)
		node = node->next;
	if (node->next)
	{
		//free node->next;
		node->next = NULL;
	}
	ret = (t_comp_cmd *)malloc(sizeof(t_comp_cmd));
	ret->tokens = pipe;
	ret->cmd_list = get_simple_cmd(pipe);
	return (ret);
}

t_pipe_seq	*ast(t_list_token *tokens)
{
	t_list_token	*node;
	t_pipe_seq		*tmp = NULL;

	node = tokens;
	while (node)
	{
		if (node->type == PIP)
		{
		
			tmp = (t_pipe_seq *)malloc(sizeof(t_pipe_seq));
			tmp->left = get_comp_cmd(tokens);
			tmp->right = ast(node->next);
			return(tmp);
		}
		node = node->next;
	}
	tmp = (t_pipe_seq *)malloc(sizeof(t_pipe_seq));
	tmp->left = get_comp_cmd(tokens);
	tmp->right = NULL;
	return(tmp);
}

int main()
{
//	char    *line = "echo \"hello world\" ; mkdir test ; cd test ; toto ; ls -a ; ls | cat | wc -c > fifi ; cat fifi";
	char    *line = "2>& 2 9>> abc <<lol >>  toto  | cat | wc -c > fifi";

	t_list_token    *tokens;
	t_pipe_seq	*cmd;
	char    **cmd_tab;
	ttyfd = fopen("/dev/ttys003", "w");
    tokens = __tokenize(line);
    token_print(tokens);
	printf("*************\n");
	sleep(2);
	/*
	should split tokens by ';' '&' '&&' '||' and specifie the two variables 
	bg = 0/1 ===> is it a background routine ? 1 : 0
	dependant = 0/1/2 (0 not dependt, 1 exec if $? == 0, 2 exec if $? != 0)
	*/
	cmd = ast(tokens); // should take tokens_tab from the split above AKA tokens_list
	return(0);
	printf("\n---------------------\n");
	print_ast(cmd);
	printf("\n---------------------\n");
	return (0);
}

//AST for pipes-seq done v1 / to do: add comp_cmd and simple_cmd to AST and generate pipe_seq list from tokens