/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_old.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:48:13 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/01 17:48:14 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"

int	ft_cd_old(char **env)
{
	char	*cwd;
	char	*tmp;

	tmp = get_var_from_tab(env, "OLDPWD");
	if (!tmp)
		return (1);
	cwd = get_pwd(env);
	if (!chdir(tmp))
	{
		change_pwd("PWD", tmp);
		ft_putstr(tmp);
		ft_putchar('\n');
		if (cwd)
			change_pwd("OLDPWD", cwd);
		free(tmp);
		free(cwd);
		return (0);
	}
	if (access(tmp, F_OK) == 0 && access(tmp, X_OK) == -1)
	{
		ft_putstr_fd("cd: permission denied: ", STDERR);
		ft_putstr_fd(tmp, STDERR);
		ft_putchar_fd('\n', STDERR);
		return (0);
	}
	ft_putstr_fd("cd: ", STDERR);
	ft_putstr_fd(tmp, STDERR);
	free(tmp);
	ft_putstr_fd(": No such file or directory.\n", STDERR);
	return (1);
}
