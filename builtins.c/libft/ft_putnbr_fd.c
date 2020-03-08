/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 05:19:32 by afaraji           #+#    #+#             */
/*   Updated: 2018/10/20 01:47:25 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long number;

	number = n;
	if (number < 0)
	{
		ft_putchar_fd('-', fd);
		number = -number;
	}
	if (number > 9)
	{
		ft_putnbr_fd((number / 10), fd);
		ft_putnbr_fd((number % 10), fd);
	}
	else
	{
		ft_putchar_fd((number + 48), fd);
	}
}
