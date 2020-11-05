/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 22:35:40 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/02 22:35:42 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

char	*copy_char_1(t_line *line, int curs)
{
	int		i;
	int		j;
	char	*to_copy;

	if (!(to_copy = (char *)malloc(sizeof(char) * (line->curs - curs + 2))))
		return (NULL);
	i = curs;
	j = 0;
	while (i <= line->curs)
	{
		to_copy[j] = line->str[i];
		i++;
		j++;
	}
	to_copy[j] = '\0';
	return (to_copy);
}

char	*copy_char_2(t_line *line, int curs)
{
	int		i;
	int		j;
	char	*to_copy;

	if (!(to_copy = (char *)malloc(sizeof(char) * curs + 1)))
		return (NULL);
	i = line->curs;
	j = 0;
	while (i <= curs)
	{
		to_copy[j] = line->str[i];
		i++;
		j++;
	}
	to_copy[j] = '\0';
	return (to_copy);
}

char	*copy_char(t_line *line, int curs)
{
	if (line->curs > curs)
		return (copy_char_1(line, curs));
	else
		return (copy_char_2(line, curs));
}

void	ft_copy(t_terminal *term, char **to_past)
{
	if (term->select->on == 1)
	{
		tputs(tgetstr("sc", NULL), 1, ft_intputchar);
		display_line_from_begin(term->line);
		tputs(tgetstr("rc", NULL), 1, ft_intputchar);
		if (*to_past)
			ft_strdel(to_past);
		*to_past = copy_char(term->line, term->select->start);
		term->select->on = 0;
	}
}
