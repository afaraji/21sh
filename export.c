/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:23:42 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/12 16:23:44 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "parse.h"
#include "builtins.h"

void	get_last_node(char *key, char *value)
{
	t_variable	*node;

	node = g_var.var;
	while (node->next)
		node = node->next;
	node->next = (t_variable *)malloc(sizeof(t_variable));
	node = node->next;
	node->key = ft_strdup(key);
	if (value == NULL)
    {
		node->value = ft_strdup("");
        node->env = 1;
    }
	else
    {
		node->value = ft_strdup(value);
        node->env = 0;
    }
	node->next = NULL;
}

void    ft_export_2(char *key, char *value)
{
    t_variable *node;

    node = g_var.var;
    while (node)
    {
        if (ft_strcmp(node->key, key) == 0)
        {
            if (value == NULL)
            {
                free(node->value);
                node->value = ft_strdup("");
            }
            else
            {
                free(node->value);
                node->value = ft_strdup(value);
            }
            node->env = 0;
        }
        else
            get_last_node(key, value);
        node = node->next;
    }
}

int     check_valid_key(char *key)
{
    int i;

    if (!(ft_isalpha(key[0])) && key[0] != '_')
    {
        ft_putstr("export: not a valid identifier.\n");
        return (1);
    }
    i = 1;
    while (key[i])
	{
		if (!(ft_isalnum(key[i])) && key[i] != '_')
		{
			ft_putstr("export: not a valid identifier.\n");
			return (1);
		}
		i++;
	}
    return (0);
}

int      search_char(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (0);
}

int     get_key_value(char *key, char *value, char *flag)
{
    int     ret;

    if ((ret = search_char(flag, '=')))
    {
        key = ft_strsub(flag, 0, ret);
        if (check_valid_key(key))
        {
            ft_strdel(&key);
            return (1);
        }
        value = ft_strdup(&(flag[ret]));
    }
    else
    {
        key = ft_strdup(flag);
        if (check_valid_key(key))
        {
            ft_strdel(&key);
            return (1);
        }
    }
    return (0);
}
