/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:15:16 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/09 17:15:17 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "parse.h"
#include "minishell.h"

void    print_env(int type)
{
    t_variable	*node;

    node = g_var.var;
    while (node)
    {
        if (type || (type == 0 && node->env == 0))
        {
            ft_putstr(node->key);
            ft_putchar('=');
            ft_putstr(node->value);
            ft_putchar('\n');
        }
        node = node->next;
    }
}

int     cd_builtin(char **av)
{
    if (av[2] == NULL)
        return (ft_cd_home());
    else
    {
        if (av[2][0] == '-' )
        {
            if (av[2][1] == '\0')
                return (ft_cd_old());
            else if (av[2][1] == 'P')
                return (ft_cd_1(av[3]));
            else if (av[2][1] == 'L')
                return (ft_cd(av[3]));
        }
        else
            return (ft_cd(av[2]));
    }
    return (1);
}

int     builtins(char *cmd, char **av)
{
    if (ft_strcmp(cmd, "echo") == 0)
        return (ft_echo(av));
    else if (ft_strcmp(av[1], "cd") == 0)
        return (cd_builtin(av));
    if (ft_strcmp(cmd, "env") == 0)
    {
        print_env(0);
        return (0);
    }
    else if (ft_strcmp(cmd, "setenv") == 0)
        return (ft_setenv(av));
    else if (ft_strcmp(cmd, "unsetenv") == 0)
        return (ft_unsetenv(av));
    return (1);
}