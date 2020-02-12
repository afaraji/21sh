/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 22:28:55 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/12 22:28:56 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char	*trim_cmd(char *s)
{
	int		i;
	int		len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	while (ft_isspace(s[len - 1]))
		len--;
	i = 0;
	while (ft_isspace(s[i]))
	{
		i++;
		len--;
	}
	if (len <= 0)
		len = 0;
	return (ft_strsub(s, i, len));
}
