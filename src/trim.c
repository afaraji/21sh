/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 14:32:03 by sazouaka          #+#    #+#             */
/*   Updated: 2020/01/18 14:32:04 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

char	*trim_pos(char *str, int curs)
{
	int		i;
	int		j;
	char	*s1;

	i = 0;
	j = 0;
	s1 = NULL;
	if (!(s1 = (char *)malloc(sizeof(char) * (ft_strlen(str)))))
		return (NULL);
	while (i < curs)
	{
		s1[i] = str[i];
		i++;
	}
	j = curs + 1;
	while (j < (int)ft_strlen(str))
	{
		s1[i] = str[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*trim_cmd(char *s)
{
	int		i;
	int		len;
	char	*str;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	len = ft_strlen(s) - 1;
	while (ft_isspace(s[len]))
		len--;
	len = len - i + 1;
	if (len < 0)
		len = 0;
	str = ft_strsub(s, i, len);
	return (str);
}
