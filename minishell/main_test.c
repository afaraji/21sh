/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:00:18 by sazouaka          #+#    #+#             */
/*   Updated: 2020/01/13 22:00:20 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*********** fix cd -P ************/
int	main (int ac, char **av, char **env)
{
	t_lst	*env_lst;

    env_lst = ft_env(env);
    if (ac >= 2)
    {
        if (ft_strcmp(av[1], "env") == 0)
            return 0 ;
        else if (ft_strcmp(av[1], "cd") == 0)
        {
            if (av[2] == NULL)
                ft_cd_home(env_lst);
            else
            {
                if (ft_strcmp(av[2], "-") == 0)
                    ft_cd_old(env_lst);
                else
                    ft_cd(av[2], env_lst);
            }
            return 0;
        }
    }
    return (0);
}