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

int     ft_export(char **flag)
{fprintf(ttyfd, "-------[export]-------\n");
    int     i;
    char    *key;
    char    *value;

    i = 1;
    value = NULL;
    while (flag[i])
    {
        if (flag[1] == NULL)
        {
			print_env(0);
            return (0);
        }
        if (get_key_value(key, value, flag[i]))
            return (1);
        ft_export_2(key, value);
        i++;
    }
    return (0);
}

void    print_env(int type)
{
    t_variable	*node;

    node = g_var.var;
    fprintf(ttyfd, "+++++++++env[%d,%s=%s]\n",type, node->key, node->value);
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
    fprintf(ttyfd, "-**-[cd]--**--\n");
    if (av[1] == NULL)
        return (ft_cd_home());
    else
    {
        if (av[1][0] == '-' )
        {
            if (av[1][1] == '\0')
                return (ft_cd_old());
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
    fprintf(ttyfd, "+-+-+->[%s]=>[%s|%s]-------\n", cmd, av[0], av[1]);
    if (ft_strcmp(cmd, "echo") == 0)
        return (ft_echo(av));
    else if (ft_strcmp(cmd, "cd") == 0)
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
    else if (ft_strcmp(cmd, "export") == 0)
        return (ft_export(av));
    return (42);
}