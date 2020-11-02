/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:01:56 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/17 16:01:57 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int		ft_cnt_parts(char *s, char c)
{
	int		cnt;

	cnt = 1;
	while (*s != '\0')
	{
		if (*s == c)
			cnt++;
		s++;
	}
	return (cnt);
}

void	get_var(char *s, int *start, int *len)
{
	int i;
	int l;

	i = *start;
	l = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		l++;
		i++;
	}
	*len = l;
}

void	init_variables(int *len, int *start)
{
	*len = 0;
	*start = 0;
}

char	**ft_strsplit_2(char *s, char c)
{
	char	**table;
	int		nb_word;
	int		i;
	int		start;
	int		len;

	if (!s)
		return (NULL);
	nb_word = ft_cnt_parts(s, c);
	if (!(table = (char **)malloc(sizeof(char *) * (nb_word + 1))))
		return (NULL);
	init_variables(&len, &start);
	i = 0;
	while (i < nb_word)
	{
		get_var(s, &start, &len);
		if (!len)
			table[i] = ft_strdup("");
		else
			table[i] = ft_strsub(s, start, len);
		start = start + len + 1;
		i++;
	}
	table[i] = NULL;
	return (table);
}
