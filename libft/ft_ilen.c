/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ilen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 23:16:56 by afaraji           #+#    #+#             */
/*   Updated: 2018/10/17 02:20:35 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ilen(int n)
{
	unsigned int	len;
	unsigned int	nb;
	int				signe;

	len = 1;
	signe = 1;
	if (n < 0)
	{
		signe = -1;
		len++;
	}
	nb = n * signe;
	while (nb > 9)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}
