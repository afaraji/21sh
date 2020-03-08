/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 08:25:38 by afaraji           #+#    #+#             */
/*   Updated: 2018/10/18 03:10:21 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;
	size_t	j;
	size_t	i;

	str = (char *)haystack;
	if (*needle == '\0')
		return (str);
	i = 0;
	j = 0;
	while (str[i] && i < len)
	{
		if (str[i] == needle[0])
		{
			j = 0;
			while (str[i + j] == needle[j] && i + j < len && needle[j])
				j++;
			if (needle[j] == '\0')
				return (&str[i]);
		}
		i++;
	}
	return (NULL);
}
