/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 18:39:05 by afaraji           #+#    #+#             */
/*   Updated: 2018/10/20 03:17:08 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itostr(int len, int i, unsigned int nb, char *str)
{
	len--;
	while (i <= len)
	{
		str[len] = (nb % 10) + '0';
		nb = nb / 10;
		len--;
	}
	return (str);
}

char		*ft_itoa(int n)
{
	char			*nstr;
	unsigned int	nb;
	int				len;
	int				i;

	i = 0;
	len = ft_ilen(n);
	nstr = (char *)malloc(sizeof(char) * (len + 1));
	if (nstr == NULL)
		return (NULL);
	nstr[len] = '\0';
	if (n < 0)
	{
		nstr[i] = '-';
		i++;
		nb = -n;
	}
	else
		nb = n;
	return (ft_itostr(len, i, nb, nstr));
}
