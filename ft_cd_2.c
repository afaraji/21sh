/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:43:17 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/01 17:43:19 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parse.h"

char	*ft_get_ld(char *cwd, char *flag)
{
	int		i;
	int		j;
	char	*tmp;
	char	*path;

	i = 0;
	while (cwd[i])
		i++;
	i--;
	if (cwd[i] != '/')
		tmp = ft_strjoin(cwd, "/");
	else
		tmp = ft_strdup(cwd);
	path = ft_strjoin(tmp, flag);
	free(tmp);
	return (path);
}

char	*get_pwd(char **env)
{
	char	*pwd;

	pwd = get_var_from_tab(env, "PWD");
	if (!pwd)
		pwd = getcwd(NULL, 0);
	return (pwd);
}

char	*get_var_from_tab(char **env, char *str)
{
	int		i;
	char	*s;
	int		len;

	i = 0;
	while (env[i])
	{
		len = 0;
		while (env[i][len])
		{
			if (env[i][len] == '=')
				break ;
			len++;
		}
		if (len >= ft_strlen(env[i]))
			return (NULL);
		s = ft_strsub(env[i], 0, len);
		if (!ft_strcmp(s, str))
		{
			free(s);
			return (ft_strdup(&env[i][len + 1]));
		}
		i++;
	}
	return (NULL);
}

int		ft_pdenied(char *flag)
{
	DIR	*dir;

	dir = NULL;
	dir = opendir(flag);
	if (dir == NULL)
	{
		if (access(flag, F_OK) == 0 && access(flag, X_OK) == -1)
			ft_putstr_fd("cd: permission denied: ", STDERR);
		else
			ft_putstr_fd("cd: no such file or directory***: ", STDERR);
		ft_putstr_fd(flag, STDERR);
		ft_putchar_fd('\n', STDERR);
		return (1);
	}
	closedir(dir);
	return (0);
}
