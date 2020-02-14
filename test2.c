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
	if (str[i] == '>' && str[i + 1] == '>')	// should escape 2nd >
		return (GRTGRT);
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
			printf("[%d:%s]", node->is_ok, node->data);
		else
		{
			printf("(%d)", node->type);
		/*	switch (node->type)
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
			case -1337:
				break;
			
			default:
				printf("[%d]", node->type);
				break;
			}   */
		}
		node = node->next;
	}
	printf("\n");
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

int main()
{
	char    *line = "echo ''hello world ; mkdir test ; cd test ; toto ; ls -a ; ls | cat | wc -c > fifi ; cat fifi";
	t_list_token    *tokens;
	char    **cmd_tab;
	char    *cmd;

    tokens = __tokenize(line);
    token_print(tokens);
	return (0);
}