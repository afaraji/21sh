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
# define DEL 0x7f
# define ENTER 0xa
# define BUFF_SIZE 4
# define RTWORD 0x8288E2
# define LFTWORD 0xA5C3
# define UPLINE 0x9188E2
# define DWNLINE 0x9FC3
# define DWNLINE 0x9FC3
# define SELECT 0x10
# define COPY 0xA7C3
# define CUT 0x8889E2
# define PAST 0x9A88E2

typedef	struct		s_line
{
	char			*str;
	int				curs;
	int				col;
	int				nline;
	int				pmt_s;
}					t_line;

typedef struct		s_hist
{
	char			*hist_str;
	int				index;
	struct s_hist	*next;
	struct s_hist	*prec;
}					t_hist;

typedef struct		s_select
{
	int				start;
	int				on;
	int				len;
}					t_select;

typedef struct		s_terminal
{
	t_line			*line;
	t_select		*select;
	int				index;
	int				buff;
}					t_terminal;

FILE	*ttyfd;

int					termtype(void);
int					ft_set_attr(int index);
char				*manage_line(char *prompt, t_hist **his_head);
t_line				*init_line(char *prompt);
void				ft_prompt(char *prompt);
int					printable(t_terminal *term, t_hist **his_head);
void				unprintable(t_terminal *term, t_hist **his, char **to_past);
int					unprintable_1(t_terminal *term, char **to_past);
int					unprintable_2(t_terminal *term);
int					ft_intputchar(int c);
void				go_left(t_line *line);
void				go_right(t_line *line);
void				go_up(t_line *line);
void				go_down(t_line *line);
void				go_home(t_line *line);
void				go_end(t_line *line);
void				del_char(t_line *line);
void				del_line(t_line *line);
char				*join_line(char *str, char c, int curs);
char				*trim_pos(char *str, int curs);
void				display_line(t_line *line);
int					get_next_line(const int fd, char **line);
t_hist				*get_his_node(char *file_str, t_hist *prec, int index);
void				get_his_list(char *file_str, t_hist **head, int index);
void				add_cmd_to_his_list(char *cmd, t_hist **his_head);
int					save_list(t_hist *his_head);
void				navigate_history(t_terminal *term, t_hist **current);
void				move_by_word(t_line *line, int buff);
char				*trim_cmd(char *s);
void				move_curs(t_terminal *term);
int					verify_new_line(t_line *line);
char				**ft_strsplit_2(char *s, char c);
int					get_lines_len(char **table, int limit);
int					is_multline(char *s);
int					len_str_from_nl(t_line *line, int pos);
t_hist				*get_node_index(t_hist **current, int index);
void				ft_copy(t_terminal *term, char **to_past);
char				*copy_char(t_line *line, int curs);
void				ft_cut(t_terminal *term, char **to_past);
void				past(t_line *line, char **to_past);
void				display_line_from_begin(t_line *line);
void				left_select(t_terminal *term);
void				right_select(t_terminal *term);
char				*readline(int prompt);
void    			free_line(t_line *line);

#endif
