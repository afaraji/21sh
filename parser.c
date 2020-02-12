/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 22:35:19 by afaraji           #+#    #+#             */
/*   Updated: 2020/01/14 22:35:22 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parse.h"
#include "lexer.c"

int		is_word(char *start, char *end)
{
	if (!start)
		return (0);
	if (!end)
	{
		if (!ft_isalpha(*start) && *start != '_')
			return (0);
		while (*start != '\0')
		{
			if (!ft_isalnum(*start) && *start != '_')
				return (0);
			start++;
		}
	}
	else
	{
		if (!ft_isalpha(*start) && *start != '_')
			return (0);
		while (start <= end)
		{
			if (!ft_isalnum(*start) && *start != '_')
				return (0);
			start++;
		}
	}
	
	return (1);
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

char *parser(char *str)
{
	int i;
	int op;
	char *new_str = (char *)malloc(sizeof(char) * 1024);
	ft_bzero(new_str, 1024);	
	i = 0;
	int j = 0;
	while(str[i])
	{
		if ((op = is_op(str, i)) < 0)
		{
			ft_putchar('|');
			ft_putnbr(op);
			ft_putchar('|');
			new_str[j++] = op;
			if (op == QUOTE || op == DQUOTE)
			{
				while (str[i] != op)
				{
					ft_putchar(str[i]);
					new_str[j++] = str[i];
					i++;
				}
			}
		}
		else
		{
			ft_putchar(str[i]);
			new_str[j++] = str[i];
		}
		i++;
	}
	ft_putchar('\n');
	return (new_str);
}

//**********************************************************
// char	*output;

// void	pipe_exp(char *str)
// {
// 	ft_putstr(str);
// 	ft_putchar('\n');
// }

// void	expression(str)
// {

// }

// void	cmd(str)
// {

// }

// void	operator_exp(str)
// {

// }

// ************

void	add_quote(t_list_token	*head, int *index, char *str)
{
	t_list_token	*node;
	int i = *index;

	node = head;
	while(node->next)
		node = node->next;
	node->next = (t_list_token *)malloc(sizeof(t_list_token));	//need protection if malloc fails.
	i++;
	while (str[i] != 39)
		i++;
	node->next->type = QUOTE;
	node->next->data = ft_strsub(str, *index + 1, i - *index - 1); // i = 0; or i = *index ?
	node->next->next = NULL;
	node->next->prec = node;
	*index = i + 1;
//	printf("index = %d *-[%c]\n", *index, str[i + 1]);
}

void	add_dquote(t_list_token	*head, int *index, char *str)		// backslash and dollar exeption
{
	t_list_token	*node;
	int i = *index;

	node = head;
	while(node->next)
		node = node->next;
	node->next = (t_list_token *)malloc(sizeof(t_list_token));	//need protection if malloc fails.
	i++;
	while (str[i] != 34 && str[i - 1] != 92)		// need testing
		i++;
	node->next->type = DQUOTE;
	node->next->data = ft_strsub(str, *index + 1, i - *index - 1);		// i = 0; or i = *index ?
	node->next->next = NULL;
	node->next->prec = node;
	*index = i + 1;
}

void	add_space(t_list_token	*head, int *index, char *str)
{
	t_list_token	*node;
	int i = *index;

	node = head;
	while(node->next)
		node = node->next;
	node->next = (t_list_token *)malloc(sizeof(t_list_token));	//need protection if malloc fails.
	node->next->type = SPACE;
	node->next->data = NULL;
	node->next->next = NULL;
	node->next->prec = node;
	while (ft_isspace(str[i]))
		i++;
	*index = i;
}

void	add_escape(t_list_token	*head, int *index, char *str)
{
	t_list_token	*node;

	node = head;
	while(node->next)
		node = node->next;
	node->next = (t_list_token *)malloc(sizeof(t_list_token));	//need protection if malloc fails.
	node->next->type = ESCAPE;
	node->next->data = ft_strsub(str, *index + 1, 1);printf("---|%s|---\n", node->next->data);
	node->next->next = NULL;
	node->next->prec = node;
	*index += 2;
}

void	add_op(t_list_token	*head, int *index, char *str, int op)
{
	t_list_token	*node;

	node = head;
	while(node->next)
		node = node->next;
	node->next = (t_list_token *)malloc(sizeof(t_list_token));	//need protection if malloc fails.
	if (op == ANDLG || op == ORLG || op == GRTGRT || op == SMLSML)
		*index += 1;
	*index += 1;
	node->next->type = op;
	node->next->data = NULL;
	node->next->next = NULL;
	node->next->prec = node;
}

void	add_word_int(t_list_token *head, int *index, char *str)
{
	int i;
	t_list_token	*node;

	i = *index;
	
	while (str[i] && is_op(str, i) == 0)
	{
		i++;
	}
	node = head;
	while(node->next)
		node = node->next;
	node->next = (t_list_token *)malloc(sizeof(t_list_token));	//need protection if malloc fails.
	node->next->type = WORD;
	node->next->data = ft_strsub(str, *index, i - *index); // i = 0; or i = *index ?
	node->next->next = NULL;
	node->next->prec = node;
	*index = i;
}

t_list_token	*tokenize(char *str)
{
	t_list_token	*line;
	int op;
	int i;

	line = (t_list_token *)malloc(sizeof(t_list_token));
	line->type = -1337;
	line->next = NULL;
	line->data = NULL;
	line->prec = NULL;
	i = 0;
	
	while(str[i])
	{
		if ((op = is_op(str, i)) < 0)
		{
			if (op == QUOTE)
			{
				add_quote(line, &i, str);
			}
			else if (op == DQUOTE)
			{
				add_dquote(line, &i, str);
			}
			else if (op == SPACE)
			{
				add_space(line, &i, str);
			}
			else if (op == ESCAPE)
			{
				add_escape(line, &i, str);
			}
			else
			{
				add_op(line, &i, str, op);
			}
		}
		else
		{
			add_word_int(line, &i, str);
		}
	}
	return (line);
}

// *************

void	token_print(t_list_token *node)
{
	while (node)
	{
		if(node->type == WORD)
			printf("(%d)%s", node->type, node->data);
		else if(node->type == QUOTE || node->type == DQUOTE)
			printf("[%s]", node->data);
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
			case -1337:
				break;
			
			default:
				printf("[%d]", node->type);
				break;
			}
		}
		node = node->next;
	}
	printf("\n");
}

void	list_token_print(t_list_token **list)
{
	int i = 0;
	while (list[i])
	{
		printf("cmd[%d]:", i);
		token_print(list[i]);
		i++;
	}
}

t_list_token	*ft_token_split2(t_list_token **node, int spliter)
{
	t_list_token	*head;
	t_list_token	*tmp;

	if ((*node)->type == -1337)
		*node = (*node)->next;
	head = *node;
	while (head && head->type == SPACE)
		head = head->next;
	while (*node && (*node)->type != spliter)
		(*node) = (*node)->next;
	if (*node && (*node)->next)
	{
		(*node) = (*node)->next;
		tmp = (*node)->prec;
		tmp->next = NULL;
		(*node)->prec = NULL;
	}
	return (head);
}

t_list_token	**ft_token_split(t_list_token *line)
{
	t_list_token	**cmd_list;
	t_list_token	*node;
	int count;
	int i;

	count = 1;
	node = line;
	while (node)
	{
		if (node->type == SMCLN)
			count++;
		node = node->next;
	}
	cmd_list = (t_list_token **)malloc(sizeof(t_list_token *) * (count + 1));
	i = 0;
	node = line;
	while (i < count)
	{
		cmd_list[i] = ft_token_split2(&line, SMCLN);
		i++;
	}
	cmd_list[i] = NULL;
	return (cmd_list);
}

char	*parser_2(char *str)
{
	t_list_token	*line;
	t_list_token	**cmd_list;
	int i;

	line = tokenize(str);
	printf("%s\n\t\t-----------------------------------\n", str);
	token_print(line);
	printf("\n\t\t-----------------------------------\n");
	// split into commands
	cmd_list = ft_token_split(line);
	list_token_print(cmd_list);
	// traitement de chaque command
	i = 0;
	while (cmd_list[i])
	{
		lexer(cmd_list[i]);
		i++;
	}
	return (NULL);
}

//**********************************************************

int main()
{
	char *line = "{ echo \"hello world\" ; mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi";
	char *parsed;
	char **cmd_tab;
	char *cmd;

//	printf("%s --> %d\n", ft_strsub(line, 6, 9 - 6 + 1),is_word(&line[6], &line[9]));
	// parsed = parser(line);
	// cmd_tab = ft_strsplit(parsed, -4);
	// for(int i = 0; cmd_tab[i] ; i++)
	// 	printf("cmd_tab[%d]:%s\n", i, cmd_tab[i]);
	// int i = 0;
	// while (cmd_tab[i])
	// {
	// 	cmd = parser_2(cmd_tab[i]);
	// 	i++;
	// }
	parser_2(line);
	return (0);
}