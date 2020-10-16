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

#include "builtins.h"
#include "parse.h"

int	ft_cd_old(char **env)
{
	char	*cwd;
	char	*tmp;

	tmp = get_var_from_tab(env, "OLDPWD");
	if (!tmp)
		return(1);
	cwd = NULL;
	cwd = getcwd(NULL, 0);
	if (cwd)
		change_pwd("OLDPWD", cwd);
	if (!chdir(tmp))
	{
		change_pwd("PWD", tmp);
		ft_putstr(getcwd(NULL, 0));
		ft_putchar('\n');
		free(tmp);
		return (0);
	}
	ft_putstr_fd("cd: ", STDERR);
	ft_putstr_fd(tmp, STDERR);
	free(tmp);
	ft_putstr_fd(": No such file or directory.\n", STDERR);
	return (1);
}
