/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:24:44 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 18:24:49 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int		do_prefix(t_cmd_prefix *prefix, t_variable *var, int env)
{
	t_cmd_prefix	*node;
	int				ret;

	ret = 0;
	do_assignement(prefix, var, env);
	node = prefix;
	while (node)
	{
		if (node->io_redirect)
		{
			ret = do_redirect(node->io_redirect);
			if (ret != 0)
				return (ret);
		}
		node = node->prefix;
	}
	return (ret);
}

char	**paths_from_env(void)
{
	char	**paths;
	char	*tmp;
	int		i;

	tmp = fetch_variables("PATH", -1);
	if (!tmp)
		return (NULL);
	paths = ft_strsplit(tmp, ':');
	ft_strdel(&tmp);
	i = 0;
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = tmp;
		i++;
	}
	paths[i] = NULL;
	return (paths);
}

char	*get_cmdpath_error(int err_no, char *str)
{
	int	typ;

	if (err_no == 1)
	{
		typ = verify_type(str);
		if (typ == 1 || typ == 3)
			ft_print(STDERR, "shell: %s: is directory\n", str);
		else
			ft_print(STDERR, "shell: %s: No such file or directory\n", str);
		return (NULL);
	}
	if (err_no == 2)
	{
		ft_print(STDERR, "shell: command not found: %s\n", str);
		return (NULL);
	}
	return (NULL);
}

char	*get_cmdpath(char *str)
{
	char	**paths;
	int		i;
	char	*tmp;

	if (!access(str, F_OK) && verify_type(str) == 2)
		return (ft_strdup(str));
	if (is_path(str))
		return (get_cmdpath_error(1, str));
	if (!(paths = paths_from_env()))
		return (get_cmdpath_error(2, str));
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], str);
		if (!access(tmp, F_OK))
		{
			free_tab(paths);
			return (tmp);
		}
		ft_strdel(&tmp);
		i++;
	}
	free_tab(paths);
	return (get_cmdpath_error(2, str));
}
