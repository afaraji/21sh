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
	int i;
	int j;

	i = 0;
	j = 0;
	char *s1 = malloc(sizeof(char)* (ft_strlen(str)));
	while(i < curs)
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
	if(j == (int)ft_strlen(str))
		i++;
	s1[i]= '\0';
	return(s1);
}
