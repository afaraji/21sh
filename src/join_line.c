/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 14:24:41 by sazouaka          #+#    #+#             */
/*   Updated: 2020/01/18 14:24:43 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

char	*join_line_1(char *str, char *s1, int i, int j)
{
	while (j < (int)ft_strlen(str))
	{
		i++;
		s1[i] = str[j];
		j++;
	}
	if (j == (int)ft_strlen(str))
		i++;
	s1[i] = '\0';
	ft_strdel(&str);
	return (s1);
}

char	*join_line(char *str, char c, int curs)
{
	int		i;
	int		j;
	char	*s1;

	i = 0;
	j = 0;
	if (c == '\n')
		return (str);
	if (!(s1 = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2))))
		return (NULL);
	while (i < curs)
	{
		s1[i] = str[i];
		i++;
	}
	s1[i] = c;
	j = curs;
	return (join_line_1(str, s1, i, j));
}
