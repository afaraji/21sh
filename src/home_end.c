/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 22:15:42 by sazouaka          #+#    #+#             */
/*   Updated: 2020/01/17 22:15:48 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

void	go_home(t_line *line)
{
	while (line->curs > 0)
		go_left(line);
}

void	go_end(t_line *line)
{
	while (line->curs < (int)ft_strlen(line->str))
		go_right(line);
}
