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
# include "ft_21sh.h"

# define LFTARROW		0x445B1B
# define RTARROW		0x435B1B
# define UPARROW		0x415B1B
# define DWNARROW		0x425B1B
# define HOME			0x485B1B
# define END			0x465B1B
# define DEL			0x7F
# define ENTER			0xA
# define BUFF_SIZE		2
# define RTWORD			0x8288E2
# define LFTWORD		0xA5C3
# define UPLINE			0x9188E2
# define DWNLINE		0x9FC3
# define SELECT			0x10
# define COPY			0xA7C3
# define CUT			0x8889E2
# define PAST			0x9A88E2
# define TAB			0x9
# define CTRL_C			0x3
# define CTRL_QUIT		0x1C
# define CTRL_D			0x4
# define CTRL_L			0xC
# define HIST_FILE		"/tmp/.myshell_history"

int					termtype(void);
int					check_termcap(void);
int					ft_set_attr(int index);
void				cpy_set_atr_ican(struct termios *src, struct termios *dst);
char				*manage_line(char *prompt, t_hist **his_head, int m_line);
t_terminal			*initiate_unprint_var(void);
t_line				*init_line(char *prompt);
void				ft_prompt(char *prompt);
int					get_current_row(void);
int					printable(t_terminal *term, t_hist **his_head, int m_line);
void				printable_1(t_terminal *term);
int					get_cmd(t_terminal *term, t_hist **his_head, int mult_line);
int					get_cmd_1(char **str1, char **str2);
int					unprintable(t_terminal *term, t_hist **his, char **to_past);
int					unprintable_1(t_terminal *term, char **to_past);
int					unprintable_2(t_terminal *term);
int					tabulation_on(t_terminal *term);
int					ft_intputchar(int c);
void				go_left(t_line *line);
void				go_left_1(t_line *line);
void				go_left_2(t_line *line, int len);
void				go_upline(t_line *line);
void				go_right(t_line *line);
void				go_right_1(t_line *line);
void				go_up(t_line *line);
void				go_up_1(t_line *line, char **table);
void				go_down(t_line *line);
void				go_down_1(t_line *line, char **table);
void				go_down_2(t_line *line);
void				go_home(t_line *line);
void				go_end(t_line *line);
void				del_char(t_line *line);
void				del_line(t_line *line);
char				*join_line(char *str, char c, int curs);
char				*join_line_1(char *str, char *s1, int i, int j);
char				*trim_pos(char *str, int curs);
void				display_line(t_line *line);
void				move_curs_right(t_line *line);
void				freeleak_up_down(t_terminal *term, t_hist *to_print);
void				freeleak_down_2(t_terminal *term, char *old_line);
char				*copy_char(t_line *line, int curs);
char				*copy_char_1(t_line *line, int curs);
char				*copy_char_2(t_line *line, int curs);
void				ft_cut(t_terminal *term, char **to_past);
void				ft_cut_1(t_terminal *term, int curs, char *tmp_s);
int					get_next_line(const int fd, char **line);
t_hist				*get_his_node(char *file_str, t_hist *prec, int index);
void				get_his_list(char *file_str, t_hist **head, int index);
void				add_cmd_to_his_list(char *cmd, t_hist **his_head, int ml);
void				add_cmd_to_hislist_1(char *cmd, int mult_line,
					t_hist **his_head);
int					save_list(void);
void				navigate_history(t_terminal *term, t_hist **current);
char				*history_search(char *str, t_hist **his_head);
char				*history_search_word(char *str);
char				*history_search_num(int index);
void				history_up(t_terminal *term, t_hist **current);
void				history_down(t_terminal *term, t_hist **curr, char *old);
void				hist_up_down(t_terminal **term, t_hist **current);
void				move_by_word(t_line *line, int buff);
void				move_by_word_1(t_line *line);
char				*trim_cmd(char *s);
void				move_curs(t_terminal *term);
int					verify_new_line(t_line *line);
char				**ft_strsplit_2(char *s, char c);
void				init_variables(int *len, int *start);
void				get_var(char *s, int *start, int *len);
int					ft_cnt_parts(char *s, char c);
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
void				left_select_1(t_line *line);
void				left_select_2(t_terminal *term);
void				right_select(t_terminal *term);
void				right_select_1(t_line *line);
void				right_select_2(t_terminal *term);
char				*readline(int prompt);
void				free_term(t_terminal **term);
int					auto_completion(t_line *line);
char				*get_path(char *str);
char				*get_path_2(char **str, int i);
int					get_path_1(char *str);
char				*get_to_cmp(char *str);
t_l					*names_list(char *str);
t_l					*get_var_list(char *str, t_l *head);
int					get_node_sum(t_l *head);
t_l					*sort_list(t_l *head);
char				**tab_from_list(t_l *head);
void				free_list(t_l *head);
void				free_tab(char **table);
char				**var_search(char *str);
t_l					*matched_f_d(DIR *d, char *str);
t_l					*matched_files_dirs(char *str);
t_l					*f_d_search(char *path, char *d_name, char *cmp, char *f_d);
char				**files_dirs_search(char *str);
char				**files_dirs_search_1(char *path, char *to_cmp, DIR *d);
char				**files_dirs_search_2(char *path);
char				*files_dirs_search_3(char *d_name, char *path);
t_l					*get_cmd_list_1(char *str, t_l *head);
t_l					*search_builtin(char *str);
int					get_path_value(char ***str);
int					cmd_path(t_l *cmd_list, char ***cmd_tab, char ***cmd_paths);
void				cmd_path_1(char **tmp, char ***cmd_paths);
void				get_cmd_list(t_l **cmd_list, char **cmd_paths, char *str);
char				**cmd_search(char *str);
int					is_path(char *str);
char				**completion_split(char *line);
char				**completion_split_1(char **table);
char				*completed_line(char *line, char *str);
t_completion		*get_completion_var(void);
void				print_result(char **t, t_line *line);
void				print_result_1(t_completion *complete, char **t,
					t_line *line);
int					get_home_path(char **str);
char				**auto_completion_1(t_line *line);
int					is_all_digits(char *s);
void				init_vars(t_l **f_dirs_list, char **file_dir, t_l **node);

#endif
