/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:00:18 by sazouaka          #+#    #+#             */
/*   Updated: 2020/10/29 23:56:26 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int			is_number(char *str)
{
	if (!str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	return (is_all_digits(str));
}

int			ft_exit(char **av)
{
	int		status;

	ft_set_attr(1);
	save_list();
	free_g_var();
	if (av[1])
	{
		if (ft_strlen(av[1]) < 10 && is_number(av[1]))
		{
			status = ft_atoi(av[1]);
			if (av[2])
				ft_print(STDERR, "exit\nshell: exit: too many arguments.\n");
		}
		else
		{
			status = 255;
			ft_print(STDERR, "exit\nshell: exit: ");
			ft_print(STDERR, "%s: numeric argument required.\n", av[1]);
		}
	}
	else
		status = 0;
	exit(status);
}

int			main(int ac, char **av, char **env)
{
	char	*line;
	int		ret;

	if (!ttyname(0) || !ttyname(1) || !ttyname(2))
		return (-1);
	line = NULL;
	ret = 0;
	ft_signal();
	if (init_shell(env))
		return (1);
	while (1)
	{
		if (ft_set_attr(0))
			return (1);
		line = readline(0);
		g_var.errno = 0;
		bg_jobs();
		if (ft_strcmp(line, "") && (ret = main_parse(trim_cmd(line))))
			exit_status(ret << 8);
		if (line)
			ft_strdel(&line);
	}
	(void)ac;
	(void)av;
	return (0);
}
