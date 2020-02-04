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

#include "readline.h"

char	*join_line(char *str, char c, int curs)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (c == '\n')
		return(str);
	char *s1 = malloc(sizeof(char)* (ft_strlen(str) + 2));
	while(i < curs)
	{
		s1[i] = str[i];
		i++;
	}
	
	s1[i] = c;
	j = curs;
	while(j < (int)ft_strlen(str))
	{
		i++;
		s1[i] = str[j];
		j++;
	}
	if(j == (int)ft_strlen(str))
		i++;
	s1[i]= '\0';
	return(s1);
}
