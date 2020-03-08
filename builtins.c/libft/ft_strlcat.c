/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 03:42:36 by afaraji           #+#    #+#             */
/*   Updated: 2018/10/17 04:55:30 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t len;
	size_t ret;
	size_t i;

	i = 0;
	len = ft_strlen(dst);
	if (size <= len)
		ret = ft_strlen(src) + size;
	else
		ret = ft_strlen(src) + len;
	while (src[i] && len + 1 < size)
	{
		dst[len] = src[i];
		len++;
		i++;
	}
	dst[len] = '\0';
	return (ret);
}
