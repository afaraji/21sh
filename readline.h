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
# define BUFF_SIZE 4
# define RTWORD 0x8288E2
# define LFTWORD 0xA5C3
# define UPLINE 0x9188E2
# define DWNLINE 0x9FC3

typedef	struct		s_line
{
	char			*str;
	char			*cmd;
	int				curs;
	int				col;
	int				row;
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

FILE	*ttyfd;

int		termtype(void);
int		ft_set_attr(void);
t_line	*init_line(char *prompt);
char	*read_line(char *prompt, t_hist **his_head);
int		ft_intputchar(int c);
void	go_left(t_line *line);
void	go_right(t_line *line);
void	go_home(t_line *line);
void	go_end(t_line *line);
void	del_char(t_line *line);
void	del_line(t_line *line);
char	*join_line(char *str, char c, int curs);
char	*trim_pos(char *str, int curs);
void	put_line_curs(t_line *line);
void	display_line(t_line *line);
int		get_next_line(const int fd, char **line);
t_hist	*get_his_node(char *file_str, t_hist *prec, int index);
void	get_his_list(char *file_str, t_hist **head, int index);
void	add_cmd_to_his_list(char *cmd, t_hist **his_head);
void	save_list(t_hist *his_head, int fd);
void	navigate_history(t_line *line, int buff, t_hist **current, int *index);
void	move_by_word(t_line *line, int buff);
char	*trim_cmd(char *s);
void	move_curs(t_line *line, int buff, int curs);
int		verify_new_line(t_line *line);
int		get_last_newline(t_line *line);
void	go_up(t_line *line, int curs);
void	go_down(t_line *line, int curs);

#endif
