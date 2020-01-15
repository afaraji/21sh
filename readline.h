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

typedef struct s_line
{
    char *str;
    int curs;
} t_line;

#endif
