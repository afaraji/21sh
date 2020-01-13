/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 07:01:09 by afaraji           #+#    #+#             */
/*   Updated: 2018/10/18 03:06:53 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (n == 0)
		return (0);
	i = 0;
	if (*s1 == '\0' || *s2 == '\0')
		return ((unsigned char)*s1 - (unsigned char)*s2);
	while ((s1[i] && s2[i]) && n - 1 > i)
	{
		i++;
		if (s1[i - 1] != s2[i - 1])
			return ((unsigned char)s1[i - 1] - (unsigned char)s2[i - 1]);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
