/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_completion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 19:33:46 by sazouaka          #+#    #+#             */
/*   Updated: 2020/10/02 19:33:48 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

t_completion	*get_completion_var(void)
{
	t_completion	*compl;

	if (!(compl = (t_completion *)malloc(sizeof(t_completion))))
		return (NULL);
	compl->total_words = 0;
	compl->str_max_len = 0;
	return (compl);
}

void			print_result_1(t_completion *compl, char **t, t_line *line)
{
	int i;

	compl->word_per_line = line->col / compl->str_max_len;
	if (compl->word_per_line == 0)
		compl->word_per_line = 1;
	compl->lines_to_print = compl->total_words / compl->word_per_line;
	compl->words_to_print = (line->row - 1) * compl->word_per_line;
	i = 0;
	while (compl->total_words)
	{
		ft_putstr(t[i]);
		compl->space = compl->str_max_len - ft_strlen(t[i]);
		while (compl->space)
		{
			ft_putchar(' ');
			compl->space--;
		}
		compl->total_words--;
		compl->words_to_print--;
		if (compl->total_words
		&& (compl->words_to_print % compl->word_per_line == 0))
			ft_putchar('\n');
		(i)++;
	}
	free(compl);
}

void			print_result(char **t, t_line *line)
{
	t_completion	*compl;

	compl = get_completion_var();
	while (t[compl->total_words])
	{
		if ((int)ft_strlen(t[compl->total_words]) > compl->str_max_len)
		{
			compl->str_max_len = ft_strlen(t[compl->total_words]) + 3;
			compl->total_words++;
		}
		else
			compl->total_words++;
	}
	print_result_1(compl, t, line);
}
