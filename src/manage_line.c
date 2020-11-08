/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 19:33:46 by sazouaka          #+#    #+#             */
/*   Updated: 2020/01/18 19:33:48 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

t_terminal	*init_term(char *prmt)
{
	int			tmp;
	t_terminal	*term;

	if (read(0, &tmp, 0) < 0)
		return (NULL);
	term = initiate_unprint_var();
	term->line = init_line(prmt);
	ft_prompt(prmt);
	return (term);
}

char		*ctrl_c_d(t_terminal *term, int mult_line)
{
	if (term->buff == CTRL_C)
	{
		free_term(&term);
		ft_putstr_fd("^C\n", 1);
		tputs(tgetstr("cd", NULL), 1, ft_intputchar);
		if (mult_line != 0)
			return (ft_strdup("\033"));
		return (ft_strdup(""));
	}
	else
	{
		free_term(&term);
		ft_putchar('\n');
		if (mult_line == 0)
			return (ft_strdup("exit"));
		return (ft_strdup("\030"));
	}
}

void		ctrl_l(char *str)
{
	ft_putstr_fd("\033[H\033[2J", 1);
	ft_prompt("$> ");
	ft_putstr(str);
}

void		unprint_manage(t_terminal *term, t_hist **his_head, char **to_past)
{
	int		unprint_ret;

	unprint_ret = unprintable(term, his_head, to_past);
	if (unprint_ret == 2)
	{
		ft_prompt("\n$> ");
		ft_putstr(term->line->str);
	}
}

char		*manage_line(char *prompt, t_hist **his_head, int mult_line)
{
	t_terminal	*term;
	char		*tmp;

	if (!(term = init_term(prompt)))
		return (NULL);
	while (1)
	{
		term->buff = 0;
		read(0, &term->buff, 4);
		if (term->buff == CTRL_C || (term->buff == CTRL_D &&
											!ft_strcmp(term->line->str, "")))
			return (ctrl_c_d(term, mult_line));
		if (term->buff == CTRL_L && mult_line == 0)
			ctrl_l(term->line->str);
		if (printable(term, his_head, mult_line))
			break ;
		else if (!(ft_isprint(term->buff)))
			unprint_manage(term, his_head, &(g_var.cpy_past));
	}
	tmp = ft_strdup(term->line->str);
	free_term(&term);
	return (tmp);
}
