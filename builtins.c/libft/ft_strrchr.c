/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 05:57:31 by afaraji           #+#    #+#             */
/*   Updated: 2018/10/17 06:08:01 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*str;

	str = (char *)s;
	len = ft_strlen(str);
	if (c == 0)
		return (&str[len]);
	while (len > 0)
	{
		if (str[len - 1] == (char)c)
			return (&str[len - 1]);
		len--;
	}
	return (NULL);
}
