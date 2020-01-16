/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 22:38:09 by sazouaka          #+#    #+#             */
/*   Updated: 2020/01/14 22:38:11 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _READLINE_H
# define _READLINE_H
# include "21sh.h"
# define LFTARROW 0x445B1B
# define RTARROW 0x435B1B
# define UPARROW 0x415B1B
# define DWNARROW 0x425B1B
# define HOME 0x485B1B
# define END 0x465B1B
# define TAB 0x465B09
# define DEL 0x7f

typedef struct s_line
{
    char *str;
    int curs;
} t_line;


int		ft_intputchar(int c);
void    go_left(t_line *line);
void    go_right(t_line *line);
void    del_char(t_line *line);

#endif

