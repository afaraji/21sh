/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:43:17 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/01 17:43:19 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

int		ft_pdenied(char *flag)
{
	DIR	*dir;

	dir = opendir(flag);
	if (dir == NULL || access(flag, X_OK) != 0)
	{
		ft_putstr("cd: permission denied: ");
		ft_putstr(flag);
		ft_putchar('\n');
		return (1);
	}
	closedir(dir);
	return (0);
}

int 	ft_cd_home(void)
{
	t_variable	*node;

	node = g_var.var;
	while (node)
	{
		if (ft_strcmp(node->key, "HOME") == 0)
		{
			if (getcwd(NULL, 0))
				change_pwd("OLDPWD", getcwd(NULL, 0));
			chdir(node->value);
			change_pwd("PWD", getcwd(NULL, 0));
			return (0);
		}
		node = node->next;
	}
	ft_putstr("cd: no home directory.\n");
    return (1);
}

int	    ft_cd_1(char *flag)
{
	char	*buff;

	if (ft_pdenied(flag))
		return (1);
	if (!(buff = (char *)malloc(sizeof(char) * 1000)))
		return (0);
	if (getcwd(NULL, 0))
		change_pwd("OLDPWD", getcwd(NULL, 0));
	chdir(flag);
	change_pwd("PWD", getcwd(NULL, 0));
	free(buff);
    return (0);
}

int 	ft_cd_2(char *flag)
{
	ft_putstr("cd: no such file or directory: ");
	ft_putstr(flag);
	ft_putchar('\n');
    return (1);
}

char	*ft_get_ld(char *cwd, char *flag)
{
	int i;
	int j;
	char	*tmp;
	
	i = 0;
	while (cwd[i])
		i++;
	i--;
	while (cwd[i] != '/')
		i--;
	j = 0;
	while (flag[j])
		j++;
	j--;
	while (j >= 0 && flag[j] != '/')
		j--;
	tmp = ft_strsub (cwd,0, i + 1);
	cwd = ft_strjoin(tmp, &flag[j + 1]);
	return (cwd);
}

int	ft_cd_3(char *flag)
{
	char	*cwd;

	if (ft_pdenied(flag))
		return (1) ;
	if (getcwd(NULL, 0))
		change_pwd("OLDPWD", getcwd(NULL, 0));
	chdir(flag);
	cwd = getcwd(NULL, 0);
	cwd = ft_get_ld(cwd, flag);
	change_pwd("PWD", cwd);
	return (0);
}

int	    ft_cd(char *flag)
{
	if (ft_strcmp(flag, ".") == 0)
		return(0);
	if (verify_type(flag) == 1)
		return (ft_cd_1(flag));
	else if (verify_type(flag) == -1)
		return (ft_cd_2(flag));
	else if (verify_type(flag) == 2)
	{
		ft_putstr("cd: not a directory: ");
		ft_putstr(flag);
		ft_putchar('\n');
        return (1);
	}
	else if (verify_type(flag) == 3)
		return (ft_cd_3(flag));
    return (0);
}
