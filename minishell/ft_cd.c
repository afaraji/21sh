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

int		ft_pdenied(char *operand)
{
	DIR	*dir;

	dir = opendir(operand);
	if (dir == NULL || access(operand, X_OK) != 0)
	{
		ft_putstr("cd: permission denied: ");
		ft_putstr(operand);
		ft_putchar('\n');
		return (1);
	}
	closedir(dir);
	return (0);
}

int 	ft_cd_home(t_lst *head)
{
	char	*buff;
	t_lst	*node;

	if (!(buff = (char *)malloc(sizeof(char) * 1000)))
		return (0);
	node = head;
	while (node)
	{
		if (ft_strcmp(node->name, "HOME") == 0)
		{
			if (getcwd(buff, 500))
				ft_change_d(head, "OLDPWD", getcwd(buff, 500));
			chdir(node->content);
			ft_change_d(head, "PWD", getcwd(buff, 500));
			free(buff);
			return (0);
		}
		node = node->next;
	}
	ft_putstr("cd: no home directory.\n");
	free(buff);
    return (1);
}

int	    ft_cd_1(char *operand, t_lst *head)
{
	char	*buff;

	if (ft_pdenied(operand))
		return (1);
	if (!(buff = (char *)malloc(sizeof(char) * 1000)))
		return (0);
	if (getcwd(buff, 500))
		ft_change_d(head, "OLDPWD", getcwd(buff, 500));
	chdir(operand);
	ft_change_d(head, "PWD", getcwd(buff, 500));
	free(buff);
    return (0);
}

int 	ft_cd_2(char *operand)
{
	ft_putstr("cd: no such file or directory: ");
	ft_putstr(operand);
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

int	ft_cd_3(char *operend, t_lst *head)
{
	char	*buff;
	char	*cwd;

	if (ft_pdenied(operend))
		return (1) ;
	if (!(buff = (char *)malloc(sizeof(char) * 1000)))
		return (1);
	if (getcwd(buff, 500))
		ft_change_d(head, "OLDPWD", getcwd(buff, 500));
	chdir(operend);
	cwd = getcwd(buff, 500);
	cwd = ft_get_ld(cwd, operend);
	ft_change_d(head, "PWD", cwd);
	free(buff);
	return (0);
}

int	    ft_cd(char *operand, t_lst *head)
{
	if (ft_strcmp(operand, ".") == 0)
		return(0);
	if (verify_type(operand) == 1)
		return (ft_cd_1(operand, head));
	else if (verify_type(operand) == -1)
		return (ft_cd_2(operand));
	else if (verify_type(operand) == 2)
	{
		ft_putstr("cd: not a directory: ");
		ft_putstr(operand);
		ft_putchar('\n');
        return (1);
	}
	else if (verify_type(operand) == 3)
		return (ft_cd_3(operand, head));
    return (0);
}
