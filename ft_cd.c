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
	if (dir == NULL)
	{
		if (access(flag, F_OK) == 0 && !access(flag, X_OK))
			ft_putstr_fd("cd: permission denied: ", STDERR);
		else
			ft_putstr_fd("cd: no such file or directory: ", STDERR);
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

char	*get_pwd(char **env)
{
	char	*pwd;

	pwd = get_var_from_tab(env, "PWD");
	if (!pwd)
		pwd = getcwd(NULL, 0);
	return (pwd);
}

int 	ft_cd_home(char **env)
{
	int		i;
	char	*path;
	char	*oldpwd;

	path = get_var_from_tab(env, "HOME");
	if (!path)
		return (1);	
	oldpwd = get_pwd(env);
	if (chdir(path))
	{
		ft_putstr("cd: ");
		ft_putstr(path);
		ft_putstr(": no such file or DIR.\n");
		free(path);
    	return (1);
	}
	if (oldpwd)
		change_pwd("OLDPWD", oldpwd);
	change_pwd("PWD", path);
	ft_putstr(path);
	ft_putchar('\n');
	free(path);
	if (oldpwd)
		free(oldpwd);
	return (0);
}

int	    ft_cd_1(char *flag, char **env)
{
	char	*oldpwd;
	char	*pwd;
	
	if (ft_pdenied(flag))
		return (1);
	oldpwd = get_pwd(env);
	if (chdir(flag))
	{
		free(oldpwd);
		return (1);
	}
	change_pwd("OLDPWD", oldpwd);
	pwd = getcwd(NULL, 0);
	change_pwd("PWD", pwd);
	ft_putstr(pwd);
	ft_putchar('\n');
	free(oldpwd);
	free(pwd);
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

int	ft_cd_3(char *flag, char **env)
{
	char	*cwd;
	char	*oldcwd;

	if (ft_pdenied(flag))
		return (1) ;
	oldcwd = get_pwd(env);
	if (chdir(flag))
	{
		if (oldcwd)
			free(oldcwd);
		return (1);
	}
	if (oldcwd)
		change_pwd("OLDPWD", oldcwd);
	if (flag[0] == '/')
	{
		cwd = ft_strdup(flag);
	}
	else
	{
		cwd = ft_get_ld(oldcwd, flag);
	}
	change_pwd("PWD", cwd);
	ft_putstr(cwd);
	ft_putchar('\n');
	free(cwd);
	if (oldcwd)
		free(oldcwd);
	return (0);
}

int	    ft_cd(char *flag, char **env)
{
	int typ;

	if (ft_strcmp(flag, ".") == 0)
		return(0);
	typ = verify_type(flag);
	if (typ == 1)
		return (ft_cd_1(flag, env));
	else if (typ == -1)
		return (ft_cd_2(flag));
	else if (typ == 2)
	{
		ft_putstr("cd: not a directory: ");
		ft_putstr(flag);
		ft_putchar('\n');
        return (1);
	}
	else if (typ == 3)
		return (ft_cd_3(flag, env));
    return (0);
}
