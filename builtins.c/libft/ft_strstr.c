/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 07:24:39 by afaraji           #+#    #+#             */
/*   Updated: 2018/10/18 02:34:22 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		len;
	char	*str;

	str = (char *)haystack;
	if (*needle == '\0')
		return (str);
	i = 0;
	len = ft_strlen(needle);
	while (str[i])
	{
		if ((str[i] == *needle) && (ft_strncmp(&str[i], needle, len) == 0))
			return (&str[i]);
		i++;
	}
	return (NULL);
}
