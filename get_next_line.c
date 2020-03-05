/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 13:48:40 by sazouaka          #+#    #+#             */
/*   Updated: 2018/11/10 09:55:04 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	static	char	*str;
	char			*tmp;
	int				i;

	if (fd < 0 || read(fd, buff, 0) < 0 || line == NULL)
		return (-1);
	if (str == NULL)
		str = ft_strnew(1);
	while ((i = read(fd, buff, BUFF_SIZE)))
	{
		buff[i] = '\0';
		tmp = str;
		str = ft_strjoin(str, buff);
		free(tmp);
		if (ft_strchr(str, '\n'))
			break ;
	}
	if (ft_strlen(str) == 0 && i == 0)
		return (0);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	*line = ft_strsub(str, 0, i);
	tmp = ft_strdup(str + i + 1);
	free(str);
	str = tmp;
	return (1);
}
