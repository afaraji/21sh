/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:35:31 by afaraji           #+#    #+#             */
/*   Updated: 2020/02/14 22:35:36 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int		interactive_mode(char **env)
{
	char	buff[BUFF_SIZE + 1];
	char	*line;
	char	*tmp;
	int		ret, i;
	char	**cmd_list;

	ret = 0;
	tmp = ft_strdup("");
	g_var.var = get_set(env);
	while ((ret = read(STDIN, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		line = ft_strjoin(tmp, buff);
		free(tmp);
		tmp = line;
	}
	cmd_list = ft_strsplit(line, '\n');
	i = 0;
	while (cmd_list[i])
	{
		ret = main_parse(cmd_list[i]);
		i++;
	}
	return (ret);
}