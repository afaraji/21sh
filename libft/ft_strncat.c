/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 03:14:44 by afaraji           #+#    #+#             */
/*   Updated: 2018/10/17 03:21:07 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(s1);
	while (s2[i] && i < n)
	{
		s1[len] = s2[i];
		i++;
		len++;
	}
	s1[len] = '\0';
	return (s1);
}
