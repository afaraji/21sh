/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 23:55:56 by afaraji           #+#    #+#             */
/*   Updated: 2018/10/17 02:35:42 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					len;
	unsigned long long	integer;
	int					signe;

	len = 0;
	integer = 0;
	signe = 1;
	while (ft_isspace(str[len]))
		len++;
	if (str[len] == '-')
		signe = -1;
	if ((str[len] == '-') || (str[len] == '+'))
		len++;
	while ((str[len] > 47) && (str[len] < 58))
	{
		integer = integer * 10;
		integer = integer + (str[len] - 48);
		len++;
	}
	if ((integer >= 9223372036854775807) && signe == 1)
		return (-1);
	if ((integer > 9223372036854775807) && signe == -1)
		return (0);
	return (integer * signe);
}
