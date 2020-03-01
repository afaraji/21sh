/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:30:47 by afaraji           #+#    #+#             */
/*   Updated: 2018/10/20 15:27:26 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_words_count(const char *str, char c)
{
	unsigned int	i;
	unsigned int	nb;

	nb = 0;
	i = 1;
	if (str[0] && str[0] != c)
		nb++;
	while (str[i])
	{
		if (str[i] != c && str[i - 1] == c)
			nb++;
		i++;
	}
	return (nb);
}
