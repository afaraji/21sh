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
/****** - fixe history : fix exit problem with terminal*****/
/****** - fixe history : fix exit problem with line->curs = 0 in the start*****/
/****** - fixe quotes qnd double quotes : even if I delet the quote it assumes that there is already a quote*****/
/****** - complete history : how about !-1 should I not put it on the history file ?*****/
/****** - complete history : make up and down moves *****/
/****** - reinicialiser termcap avant exit *****/
/****** - curs need to go up when delet on multiline *****/
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
void	is_dquote(t_line *line)
{
	ft_prompt("dquote> ");
	line->pmt_s = ft_strlen("dquote> ");
	line->curs = 0;
	line->str = ft_strdup("");
}
/*********************************************************/
void	is_quote(t_line *line)
{
	ft_prompt("quote> ");
	line->pmt_s = ft_strlen("quote> ");
	line->curs = 0;
	line->str = ft_strdup("");
}
/*********************************************************/
void	add_cmd_to_his_list(char *cmd, t_hist **his_head)
{
	t_hist	*node;
	int		i;

	node = *his_head;
	while (node->next)
	{
		node = node->next;
	}
	i = 0;
	while (cmd[i])
		i++;
	node->next = get_his_node(cmd, node);
}
/*********************************************************/
// int	verify_quote(t_line *line)
// {
// 	int i;

// 	i = 0;
// 	while (line->cmd[i])
// 	{
// 		if (line->cmd[i] == 34)
// 		{
// 			i++;
// 			while (line->cmd[i] && line->cmd[i] != 34)
// 				i++;
// 			if (i ==  (int)ft_strlen(line->cmd))
// 				return (1);
// 		}
// 		else if (line->cmd[i] == 39)
// 		{
// 			i++;
// 			while (line->cmd[i] && line->cmd[i] != 39)
// 				i++;
// 			if (i ==  (int)ft_strlen(line->cmd))
// 				return (2);
// 		}
// 		i++;
// 	}
// 	return (0);
//}
/*********************************************************/
void	get_cmd(t_line *line, char buff, t_hist **his_head)
{
	line->str = join_line(line->str, buff, line->curs);
	display_line(line);
	go_right(line);
	if (buff == ENTER)
	{
		line->cmd = ft_strjoin(line->cmd, line->str);
		add_cmd_to_his_list(line->cmd, his_head);
		// if (verify_quote(line) == 1)
		// 	is_dquote(line);
		// else if (verify_quote(line) == 2)
		// 	is_quote(line);
	}
}
/*********************************************************/
void move_curs(t_line *line, int buff, t_hist **current)
{
	int i;

	i = line->curs;
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
	else if (buff == UPARROW)
	{
    	//fprintf(ttyfd, "------------> line->curs : |%d|\n", line->curs);
		while (i > 0)
		{
			go_left(line);
			del_char(line);
			i--;
		}
		ft_strdel(&line->str);
		line->str = ft_strdup((*current)->hist_str);
		ft_putstr_fd(line->str, 1);
		line->curs = ft_strlen((*current)->hist_str);
		if ((*current)->prec)
			*current = (*current)->prec;
	}
}
/*********************************************************/
char	*read_line(char *prompt, t_hist **his_head)
{
	int		buff;
	t_line		*line;
	t_hist *current;
	int i;

	buff = 0;
	line = init_line(prompt);
	if (read(0, &buff, 0) < 0)
		return(NULL);
	ft_prompt(prompt);
	current = *his_head;
	while (current->next)
		current = current->next;
	while (1)
	{
		buff = 0;
		read(0, &buff, 4);
		if ((ft_isprint(buff) || buff == ENTER))
		{
			get_cmd(line, buff, his_head);
			if (buff == ENTER /*&& verify_quote(line) == 0*/)
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
			move_curs(line, buff, &current);
	}
	fprintf(ttyfd, "------------> line->cmd : |%s|\n", line->cmd);
	return (line->cmd);
}
