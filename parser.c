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
	if (str[i] == ' ')
		return (SPACE);
	if (str[i] == 39)
		return (QUOTE);
	if (str[i] == '"')
		return (DQUOTE);
	if (str[i] == ';')
		return (SMCLN);
	// if (str[i] == '&' && str[i + 1] == '&')	// should escape 2nd &
	// 	return (ANDLG);
	// if (str[i] == '|' && str[i + 1] == '|')	// should escape 2nd |
	// 	return (ORLG);
	if (str[i] == '|')
		return (PIP);
	if (str[i] == '&')
		return (BGJOB);
	if (str[i] == 92)
		return (ESCAPE);
	// if (str[i] == '>' && str[i + 1] != '>')	// should escape 2nd >
	// 	return (GRTGRT);
	// if (str[i] == '<' && str[i + 1] != '<')	// should escape 2nd <
	// 	return (SMLSML);
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

	i = 0;
	while(str[i])
	{
		if ((op = is_op(str, i)) < 0)
		{
			ft_putchar('|');
			ft_putnbr(op);
			ft_putchar('|');
			if (op == QUOTE || op == DQUOTE)
			{
				while (str[i] != op)
				{
					ft_putchar(str[i]);
					i++;
				}
			}
		}
		else
		{
			ft_putchar(str[i]);
		}
		i++;
	}
	ft_putchar('\n');
	return (NULL);
}

int main()
{
	char *line = "mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi";
	char *parsed;
	printf("%s --> %d\n", ft_strsub(line, 6, 9 - 6 + 1),is_word(&line[6], &line[9]));

	parsed = parser(line);
	return (0);
}