/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 14:32:03 by sazouaka          #+#    #+#             */
/*   Updated: 2020/01/18 14:32:04 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

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
