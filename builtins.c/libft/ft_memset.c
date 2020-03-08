/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 18:54:08 by afaraji           #+#    #+#             */
/*   Updated: 2018/10/17 02:28:09 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char			*pb;
	unsigned char	car;

	pb = b;
	car = (unsigned char)c;
	while (len--)
	{
		*pb++ = car;
	}
	return (b);
}
