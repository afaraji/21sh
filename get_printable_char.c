/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_printable_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <sazouaka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:03:32 by sazouaka          #+#    #+#             */
/*   Updated: 2020/03/04 00:03:34 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "parse.h"

int				is_all_digits(char *s); // put it in parse.h

char	*history_search_num(int index)
{
	t_hist	*node;

	node = g_var.history;
	while (node->next)
		node = node->next;//get the max value
	if (index < 0)
		index = node->index + index + 1;
	if (index < 1 || index > node->index)
		return (NULL);
	node = g_var.history;
	while (node)
	{
		if (node->index == index)
			return (ft_strdup(node->hist_str));
		node = node->next;
	}
	return (NULL);	
}

char	*history_search_word(char *str)
{
	int len;
	t_hist	*node;

	if (!str || !*str)
		return (NULL);
	node = g_var.history;
	len = ft_strlen(str);
	while (node->next)
		node = node->next;
	while (node)
	{
		if (!(ft_strncmp(str, node->hist_str, len)))
			return (ft_strdup(node->hist_str));
		node = node->prec;
	}
	return (NULL);	
}

char	*history_search(char *str, t_hist **his_head)
{
	char	*cmd;
	char	*tmp;

	if (!str || !(*his_head))
		return (NULL);
	if (ft_strcmp(str, "!") == 0)
		cmd = history_search_num(-1);
	else if ((is_all_digits(str) || (str[0] == '-' && is_all_digits(str + 1))))
		cmd = history_search_num(atoi(str));
	else
		cmd = history_search_word(str);
	return (cmd);
}

void	get_cmd(t_terminal *term, t_hist **his_head, int mult_line)
{
	char	*tmp;

	term->line->str = join_line(term->line->str, term->buff, term->line->curs);
	display_line(term->line);
	go_right(term->line);
	if (term->buff == ENTER)
	{
		tmp = term->line->str;
		term->line->str = trim_cmd(term->line->str);
		free(tmp);
		if (term->line->str[0] == '!' && term->line->str[1])
		{
			tmp = history_search(term->line->str + 1, his_head);
			if (tmp)
			{
				free(term->line->str);
				term->line->str = ft_strdup(tmp);
				free(tmp);
			}
			else
			{
				ft_putstr_fd("\n21sh: ", STDERR);
				ft_putstr_fd(term->line->str, STDERR);
				ft_putstr_fd(": event not found\n", STDERR);
				return;
			}
		}
		if (ft_strcmp(term->line->str, "") != 0)
			add_cmd_to_his_list(term->line->str, his_head, mult_line);
		else
			free(term->line->str);
	}
}

void	printable_1(t_terminal *term)
{
	term->select->on = 0;
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	display_line_from_begin(term->line);
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
}

int		printable(t_terminal *term, t_hist **his_head, int mult_line)
{
	int	curs;

	if ((ft_isprint(term->buff) || term->buff == ENTER))
	{
		if (term->select->on == 1)
			printable_1(term);
		else
		{
			get_cmd(term, his_head, mult_line);
			if (term->buff == ENTER)
			{
				curs = term->line->curs;
				while (curs <= (int)ft_strlen(term->line->str))
				{
					go_right(term->line);
					curs++;
				}
				return (1);
			}
		}
	}
	return (0);
}
