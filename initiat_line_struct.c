/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiat_line_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:00:56 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/04 00:00:57 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_line	*init_line(char *prompt)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	line->curs = 0;
	line->str = ft_strdup("");
	line->pmt_s = ft_strlen(prompt) + 1;
	line->col = tgetnum("co");
	return (line);
}
