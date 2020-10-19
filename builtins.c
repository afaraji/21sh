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
#include "builtins.h"

int     ft_export(char **flag, char **env)
{
    int     i;
    char    *key;
    char    *value;

    i = 1;
    if (flag[1] == NULL)
    {
        print_env(env);
        return (0);
    }
    value = NULL;
    while (flag[i])
    {
       
        if (get_key_value(&key, &value, flag[i]))
            return (1);
        ft_export_2(key, value);
        ft_strdel(&key);
        ft_strdel(&value);
        i++;
    }
    return (0);
}

void    print_env(char **env)
{
    int     i;

    if (!env)
        return;
    i = 0;
    while (env[i])
    {
        ft_putstr(env[i]);
        ft_putchar('\n');
        i++;
    }
}

int     cd_builtin(char **av, char **env)
{
    if (av[1] == NULL)
        return (ft_cd_home(env));
    else
    {
        if (av[1][0] == '-' )
        {
            if (av[1][1] == '\0')
                return (ft_cd_old(env));
            else if (av[1][1] == 'P')
                return (ft_cd_1(av[2]));
            else if (av[1][1] == 'L')
                return (ft_cd(av[2]));
        }
        else
            return (ft_cd(av[1]));
    }
    return (1);
}

int     builtins(char *cmd, char **av, char **env)
{// need verification !! n oublie pas return value
    if (ft_strcmp(cmd, "echo") == 0)
        return (ft_echo(av));
    else if (ft_strcmp(cmd, "cd") == 0)
        return (cd_builtin(av, env));
    if (ft_strcmp(cmd, "env") == 0)
    {
        print_env(env);
        return (0);
    }
    else if (ft_strcmp(cmd, "setenv") == 0)
        return (ft_setenv(av));
    else if (ft_strcmp(cmd, "unsetenv") == 0)
        return (ft_unsetenv(av));
    else if (ft_strcmp(cmd, "export") == 0)
        return (ft_export(av, env));
    return (42);
}