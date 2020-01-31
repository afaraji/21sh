/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 22:38:09 by sazouaka          #+#    #+#             */
/*   Updated: 2020/01/14 22:38:11 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _READLINE_H
# define _READLINE_H
# include "21sh.h"
# define LFTARROW 0x445B1B
# define RTARROW 0x435B1B
# define UPARROW 0x415B1B
# define DWNARROW 0x425B1B
# define HOME 0x485B1B
# define END 0x465B1B
# define TAB 0x465B09
# define DEL 0x7f
# define ENTER 0xa

typedef struct s_line
{
    char *str;
    char *cmd;
    int curs;
    int col;
    int row;
    int pmt_s;
} t_line;

FILE *ttyfd;

int     termtype(void);
int     ft_set_attr(void);
t_line	*init_line(char *prompt);
char	*read_line(char *prompt);
int		ft_intputchar(int c);
void    go_left(t_line *line);
void    go_right(t_line *line);
void    go_home(t_line *line);
void    go_end(t_line *line);
void    del_char(t_line *line);
char	*join_line(char *str, char c, int curs);
char	*trim_pos(char *str, int curs);
void	put_line_curs(t_line *line);
void	display_line(t_line *line);

#endif

// col++;
// if (col != tgetnum("co") && col != i)
// 	put_line_curs(&line);
// else if (col == tgetnum("co")|| col == i)
// {
// 	/************************************************/
// 	/***** need to check this part with hajar *******/
// 	/************************************************/
// 	put_line_curs(&line);
// 	tputs(tgetstr("do", NULL), 1, ft_intputchar);
// 	coef++;
// 	i = coef * tgetnum("co");
// }