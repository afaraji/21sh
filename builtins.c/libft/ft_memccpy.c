/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 23:16:16 by afaraji           #+#    #+#             */
/*   Updated: 2018/10/17 02:45:42 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*s;

	s = (unsigned char *)src;
	i = 0;
	while ((i < n) && (s[i] != (unsigned char)c))
		i++;
	if (n != i)
	{
		ft_memcpy(dst, src, i + 1);
		return (&dst[i + 1]);
	}
	ft_memcpy(dst, src, i);
	return (NULL);
}
