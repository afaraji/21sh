/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 19:33:46 by sazouaka          #+#    #+#             */
/*   Updated: 2020/01/18 19:33:48 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"


/*****************************************************************/
/****** - manage multiple spaces on moving left and right by word *******/
/****** - reinicialiser termcap avant exit *****/
/****** - find a solution for copy past with mouse *******/
/****************************************************************/
t_line	*init_line(char *prompt)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	line->curs = 0;
	line->cmd = ft_strdup("");
	line->str = ft_strdup("");
	line->pmt_s = ft_strlen(prompt);
	line->col = tgetnum("co");
	return (line);
}
/*********************************************************/
void	ft_prompt(char *prompt)
{
	ft_putstr("\x1B[35m");
	ft_putstr(prompt);
	ft_putstr("\x1b[39m");
}
/*********************************************************/
void	display_line(t_line *line)
{
	int	i;

	tputs(tgetstr("cd", NULL), 1, ft_intputchar);
	tputs(tgetstr("sc", NULL), 1, ft_intputchar);
	i = line->curs;
	while(i < (int)ft_strlen(line->str))
	{
		ft_putchar(line->str[i]);
		i++;
	}
	tputs(tgetstr("rc", NULL), 1, ft_intputchar);
}
/*********************************************************/
char	*ft_trim(char *s)
{
	int		i;
	int		len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	while (ft_isspace(s[len - 1]))
		len--;
	i = 0;
	while (ft_isspace(s[i]))
	{
		i++;
		len--;
	}
	if (len <= 0)
		len = 0;
	return (ft_strsub(s, i, len));
}
/*********************************************************/
void	get_cmd(t_line *line, char buff, t_hist **his_head)
{
	line->str = join_line(line->str, buff, line->curs);
	display_line(line);
	go_right(line);
	if (buff == ENTER)
	{
		line->cmd = ft_trim(ft_strjoin(line->cmd, line->str));
		if (ft_strcmp(line->cmd, "") != 0)
			add_cmd_to_his_list(line->cmd, his_head);
	}
}
/*********************************************************/
t_hist	*get_node_index(t_hist **current, int index)
{
	t_hist *node;

	node = *current;
	if(index == 0)
	{
		while (node->next)
			node = node->next;
		return (node);
	}
	while (node)
	{
		if (node->index == index)
		{
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}
/*********************************************************/
void move_curs(t_line *line, int buff, t_hist **current, int *index)
{
	t_hist *to_print;
	int last;
	int i;
	static char *old_line = NULL;

	if (*index == 0 || *index == (get_node_index(current, 0))->index + 1)
		old_line = ft_strdup(line->str);
	i = 0;
	if (buff == LFTARROW)
		go_left(line);
	else if (buff == RTARROW)
		go_right(line);
	else if (buff == DEL)
		del_char(line);
	else if (buff == HOME)
		go_home(line);
	else if (buff == END)
		go_end(line);
	else if (buff == RTWORD && !(ft_isspace(line->str[line->curs])))
	{
		while (line->curs < (int)ft_strlen(line->str) && !(ft_isspace(line->str[line->curs])))
			go_right(line);
		while (line->curs > 0  && ft_isspace(line->str[line->curs]))
		 	go_right(line);
	}
	else if (buff == RTWORD && ft_isspace(line->str[line->curs]))
	{
		while (line->curs < (int)ft_strlen(line->str)  && ft_isspace(line->str[line->curs]))
		 	go_right(line);
	}
	else if (buff == LFTWORD && !(ft_isspace(line->str[line->curs])))
	{
		if (line->curs == (int)ft_strlen(line->str)/* || ft_isspace(line->str[line->curs - 1])*/)
		{
			// if (ft_isspace(line->str[line->curs - 1]))
			// 	go_left(line);
			go_left(line);
			while (line->curs > 0  && !(ft_isspace(line->str[line->curs - 1])))
				go_left(line);
		}
		else if (ft_isspace(line->str[line->curs - 1]))
		{
			go_left(line);
			while (line->curs > 0  && ft_isspace(line->str[line->curs]))
				go_left(line);
			while (line->curs > 0  && !(ft_isspace(line->str[line->curs])) && !(ft_isspace(line->str[line->curs - 1])))
				go_left(line);
		}
		while (line->curs > 0  && !(ft_isspace(line->str[line->curs])) && !(ft_isspace(line->str[line->curs - 1])))
			go_left(line);
	}
	else if (buff == LFTWORD && ft_isspace(line->str[line->curs]))
	{
		while (line->curs > 0  && ft_isspace(line->str[line->curs]))
		 	go_left(line);
		while (line->curs > 0  && !(ft_isspace(line->str[line->curs])) && !(ft_isspace(line->str[line->curs - 1])))
			go_left(line);
	}
	else if (buff == UPARROW)
	{
		if (*index == 0)
		{
			to_print = get_node_index(current, *index);
			del_line(line);
			*index = to_print->index;
			ft_strdel(&line->str);
			line->str = ft_strdup(to_print->hist_str);
			ft_putstr_fd(line->str, 1);
			line->curs = ft_strlen(to_print->hist_str);
		}
		else if (*index - 1 > 0)
		{
			(*index)--;
			to_print = get_node_index(current, *index);
			del_line(line);
			ft_strdel(&line->str);
			line->str = ft_strdup(to_print->hist_str);
			ft_putstr(line->str);
			line->curs = ft_strlen(to_print->hist_str);
		}
	}
	else if (buff == DWNARROW)
	{
		last = (get_node_index(current, 0))->index;
		if (*index + 1 <= last && *index)
		{
			(*index)++;
			to_print = get_node_index(current, *index);
			del_line(line);
			ft_strdel(&line->str);
			line->str = ft_strdup(to_print->hist_str);
			ft_putstr(line->str);
			line->curs = ft_strlen(to_print->hist_str);
		}
		else if (*index == last)
		{
			del_line(line);
			ft_strdel(&line->str);
			line->str = ft_strdup(old_line);
			ft_putstr(line->str);
			line->curs = ft_strlen(old_line);
			(*index)++;
		}
	}
}
/*********************************************************/
char	*read_line(char *prompt, t_hist **his_head)
{
	int		buff;
	t_line		*line;
	int i;
	int index;

	buff = 0;
	line = init_line(prompt);
	if (read(0, &buff, 0) < 0)
		return(NULL);
	ft_prompt(prompt);
	index = 0;
	while (1)
	{
		buff = 0;
		read(0, &buff, 4);
		if ((ft_isprint(buff) || buff == ENTER))
		{
			get_cmd(line, buff, his_head);
			if (buff == ENTER)
			{
				i = line->curs;
				while (i <= (int)ft_strlen(line->str))
				{
					go_right(line);
					i++;
				}
				break;
			}	
		}
		else
			move_curs(line, buff, his_head, &index);
	}
	fprintf(ttyfd, "------------> line->cmd : |%s|\n", line->cmd);
	return (line->cmd);
}
