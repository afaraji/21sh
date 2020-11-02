/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_by_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 21:29:19 by sazouaka          #+#    #+#             */
/*   Updated: 2020/02/12 21:29:20 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

void	move_by_word_1(t_line *line)
{
	if (line->curs == (int)ft_strlen(line->str))
	{
		go_left(line);
		while (line->curs > 0 && ft_isspace(line->str[line->curs - 1]))
			go_left(line);
		while (line->curs > 0 && !(ft_isspace(line->str[line->curs - 1])))
			go_left(line);
	}
	else if (ft_isspace(line->str[line->curs - 1]))
	{
		go_left(line);
		while (line->curs > 0 && ft_isspace(line->str[line->curs]))
			go_left(line);
		while (line->curs > 0 && !(ft_isspace(line->str[line->curs]))
		&& !(ft_isspace(line->str[line->curs - 1])))
			go_left(line);
	}
	while (line->curs > 0 && !(ft_isspace(line->str[line->curs]))
	&& !(ft_isspace(line->str[line->curs - 1])))
		go_left(line);
}

void	move_by_word(t_line *line, int buff)
{
	if (buff == RTWORD && !(ft_isspace(line->str[line->curs])))
	{
		while (line->curs < (int)ft_strlen(line->str)
		&& !(ft_isspace(line->str[line->curs])))
			go_right(line);
		while (line->curs > 0 && ft_isspace(line->str[line->curs]))
			go_right(line);
	}
	else if (buff == RTWORD && ft_isspace(line->str[line->curs]))
	{
		while (line->curs < (int)ft_strlen(line->str)
		&& ft_isspace(line->str[line->curs]))
			go_right(line);
	}
	else if (buff == LFTWORD && ft_isspace(line->str[line->curs]))
	{
		while (line->curs > 0 && ft_isspace(line->str[line->curs]))
			go_left(line);
		while (line->curs > 0 && !(ft_isspace(line->str[line->curs]))
		&& !(ft_isspace(line->str[line->curs - 1])))
			go_left(line);
	}
	else if (buff == LFTWORD && !(ft_isspace(line->str[line->curs])))
		move_by_word_1(line);
}
