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

#include "builtins.h"
#include "parse.h"

int		ft_pdenied(char *flag)
{
	DIR	*dir;

	dir = opendir(flag);
	if (dir == NULL || access(flag, X_OK) != 0)
	{
		ft_putstr_fd("cd: permission denied: ", STDERR);
		ft_putstr_fd(flag, STDERR);
		ft_putchar_fd('\n', STDERR);
		return (1);
	}
	closedir(dir);
	return (0);
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
			if(env[i][len] == '=')
				break;
			len++;
		}
		if (len >= ft_strlen(env[i]))
			return (NULL);
		s = ft_strsub(env[i], 0, len);
		if(!ft_strcmp(s, str))
		{
			free(s);
			return (ft_strdup(&env[i][len + 1]));
		}
		i++;
	}
	return (NULL);
}

int 	ft_cd_home(char **env)
{
	int		i;
	char	*path;

	
	path = get_var_from_tab(env, "HOME");
	if (!path)
		return (1);		
	if (getcwd(NULL, 0))
		change_pwd("OLDPWD", getcwd(NULL, 0));
	if (chdir(path))
	{
		ft_putstr("cd: ");
		ft_putstr(path);
		ft_putstr(": no such file or DIR.\n");
		free(path);
    	return (1);
	}
	free(path);
	if (getcwd(NULL, 0))
	{
		change_pwd("PWD", getcwd(NULL, 0));
		ft_putstr(getcwd(NULL, 0));
		ft_putchar('\n');
	}
	return (0);
}

int	    ft_cd_1(char *flag)
{
	if (ft_pdenied(flag))
		return (1);
	if (getcwd(NULL, 0))
		change_pwd("OLDPWD", getcwd(NULL, 0));
	if (chdir(flag))
		return (1);
	change_pwd("PWD", getcwd(NULL, 0));
	ft_putstr(getcwd(NULL, 0));
	ft_putchar('\n');
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
	// free(cwd); // free if getcwd allocate mem
	cwd = ft_strjoin(tmp, &flag[j + 1]);
	free(tmp);
	return (cwd);
}

int	ft_cd_3(char *flag)
{
	char	*cwd;

	if (ft_pdenied(flag))
		return (1) ;
	if (getcwd(NULL, 0))
		change_pwd("OLDPWD", getcwd(NULL, 0));
	if (chdir(flag))
		return (1);
	ft_putstr(getcwd(NULL, 0));
	ft_putchar('\n');
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
