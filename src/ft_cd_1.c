/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:43:17 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/01 17:43:19 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int		ft_cd_home(char **env)
{
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

int		ft_cd_1(char *flag, char **env)
{
	char	*oldpwd;
	char	*pwd;

	if (ft_pdenied(flag))
		return (1);
	oldpwd = get_pwd(env);
	if (chdir(flag))
	{
		ft_strdel(&oldpwd);
		return (1);
	}
	change_pwd("OLDPWD", oldpwd);
	pwd = getcwd(NULL, 0);
	change_pwd("PWD", pwd);
	ft_putstr(pwd);
	ft_putchar('\n');
	ft_strdel(&oldpwd);
	ft_strdel(&pwd);
	return (0);
}

int		ft_cd_2(char *flag)
{
	ft_putstr("cd: no such file or directory: ");
	ft_putstr(flag);
	ft_putchar('\n');
	return (1);
}

int		ft_cd_3(char *flag, char **env)
{
	char	*cwd;
	char	*oldcwd;

	if (ft_pdenied(flag))
		return (1);
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
		cwd = ft_strdup(flag);
	else
		cwd = ft_get_ld(oldcwd, flag);
	change_pwd("PWD", cwd);
	ft_putstr(cwd);
	ft_putchar('\n');
	free(cwd);
	if (oldcwd)
		free(oldcwd);
	return (0);
}

int		ft_cd(char *flag, char **env)
{
	int typ;

	if (ft_strcmp(flag, ".") == 0)
		return (0);
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
