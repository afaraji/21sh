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
	// fprintf(ttyfd, "------>here is str len : %d\n", (int)ft_strlen(str));
	// fprintf(ttyfd, "------>here is curs pos : %d\n", j);
	// fprintf(ttyfd, "------>here is i : %d\n", i);
	while (j < (int)ft_strlen(str))
	{
	//	fprintf(ttyfd, "------>here is str : %s\n", str);
	//	fprintf(ttyfd, "------>here is s1 : %s\n", s1);
		s1[i] = str[j];
		i++;
		j++;
	}
	if(j == (int)ft_strlen(str))
		i++;
	s1[i]= '\0';
	fprintf(ttyfd, "----------->here is final s1 : %s\n", s1);
	return(s1);
}
