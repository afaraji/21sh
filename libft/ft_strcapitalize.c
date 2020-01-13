/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 13:10:56 by afaraji           #+#    #+#             */
/*   Updated: 2018/10/24 08:26:47 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *str)
{
	int i;

	ft_strlowcase(str);
	i = 0;
	if (str[i] && str[i] <= 'z' && str[i] >= 'a')
		str[i] = str[i] - 32;
	i++;
	while (str[i])
	{
		if (str[i] <= 'z' && str[i] >= 'a')
		{
			if ((str[i - 1] > 0 && str[i - 1] < 48) ||
					(str[i - 1] > 57 && str[i - 1] < 65))
				str[i] = str[i] - 32;
		}
		i++;
	}
	return (str);
}
