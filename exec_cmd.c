 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:53:40 by afaraji           #+#    #+#             */
/*   Updated: 2020/01/13 20:53:42 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include <stdarg.h>

void fatal(const char *str, ...)
{
    va_list args;
    
}

inline bool toto(void)
{
    return (true);
}
int main(void)
{
    char *line = "mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi";
    printf("|%s|\n", line);
    fatal("expesad looool\n");
    return (0);
}