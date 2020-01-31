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
	static	char	*str[256];
	int				ret;
	int				i;

	i = 0;
	if (fd < 0 || read(fd, buff, 0) < 0 || line == NULL)
		return (-1);
	if (str[fd] == NULL)
		str[fd] = ft_strnew(1);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		str[fd] = ft_strjoin(str[fd], buff);
		if (ft_strchr(str[fd], '\n'))
			break ;
	}
	if (ft_strlen(str[fd]) == 0 && ret == 0)
		return (0);
	while (str[fd][i] != '\n' && str[fd][i] != '\0')
		i++;
	*line = ft_strsub(str[fd], 0, i);
	str[fd] = ft_strdup(str[fd] + i + 1);
	return (1);
}
