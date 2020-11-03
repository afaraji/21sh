/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:30:05 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 18:30:12 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

void	exit_status(int status)
{
	t_variable *tmp;

	g_var.exit_status = WEXITSTATUS(status);
	tmp = g_var.var;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "?"))
		{
			free(tmp->value);
			tmp->value = ft_itoa(g_var.exit_status);
			break ;
		}
		tmp = tmp->next;
	}
}

int		is_alldigit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		check_fd(int fd, int io)
{
	struct stat	buffer;
	int			status;
	long		ret;

	status = fstat(fd, &buffer);
	if (io == 0)
	{
		ret = read(fd, NULL, 0);
	}
	else
	{
		ret = write(fd, NULL, 0);
	}
	if (status < 0 || ret < 0)
		return (0);
	return (1);
}
