/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:04:24 by afaraji           #+#    #+#             */
/*   Updated: 2020/01/13 20:04:34 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "../libft/libft.h"

typedef	struct			s_line
{
	char				*str;
	int					init_pos;
	int					curs;
	int					col;
	int					row;
	int					pmt_s;
}						t_line;

typedef struct			s_hist
{
	char				*hist_str;
	int					index;
	struct s_hist		*next;
	struct s_hist		*prec;
}						t_hist;

typedef struct			s_select
{
	int					start;
	int					on;
	int					len;
}						t_select;

typedef struct			s_terminal
{
	t_line				*line;
	t_select			*select;
	int					tab_on;
	int					index;
	int					buff;
}						t_terminal;

typedef struct			s_completion
{
	int					space;
	int					total_words;
	int					str_max_len;
	int					word_per_line;
	int					lines_to_print;
	int					words_to_print;
}						t_completion;

typedef struct			s_l
{
	char				*data;
	struct s_l			*next;
}						t_l;

typedef struct			s_list_token
{
	int					type;
	char				*data;
	struct s_list_token	*next;
	struct s_list_token	*prec;
	int					is_ok;
}						t_list_token;

typedef struct			s_alias
{
	char				*key;
	char				*sub;
	struct s_alias		*next;
}						t_alias;

typedef struct			s_variable
{
	int					env;
	char				*key;
	char				*value;
	struct s_variable	*next;
}						t_variable;
/*
**env == 0 --> part of env(eg. export).
**env == 1 --> part of set && only tmp.
**env == 2 --> part of set && permanent and read only.
*/

typedef struct			s_proc
{
	pid_t				ppid;
	int					index;
	int					status;
	int					done;
	char				*str;
	struct s_proc		*next;
}						t_proc;

typedef struct			s_shell_var
{
	int					errno;
	int					exit_status;
	int					sig;
	char				*cpy_past;
	t_alias				*aliases;
	t_variable			*var;
	t_hist				*history;
	t_proc				*proc;
}						t_shell_var;

typedef struct			s_io_redirect
{
	int					redirect_type;
	int					io_num;
	char				*filename;
}						t_io_redirect;

typedef struct			s_cmd_suffix
{
	t_io_redirect		*io_redirect;
	char				*word;
	struct s_cmd_suffix	*suffix;
}						t_cmd_suffix;

typedef struct			s_cmd_prefix
{
	t_io_redirect		*io_redirect;
	t_variable			*ass_word;
	struct s_cmd_prefix	*prefix;
}						t_cmd_prefix;

typedef struct			s_simple_cmd
{
	char				*word;
	char				*name;
	t_cmd_prefix		*prefix;
	t_cmd_suffix		*suffix;
}						t_simple_cmd;

typedef struct			s_pipe_seq
{
	t_simple_cmd		*left;
	struct s_pipe_seq	*right;
}						t_pipe_seq;

typedef struct			s_and_or
{
	int					dependent;
	t_pipe_seq			*ast;
	struct s_and_or		*next;
}						t_and_or;

/*
**dependent : (0';&' not dependt, 1 exec if $? == 0 '&&',
**2 exec if $? != 0 '||')
*/

typedef struct			s_cmdlist
{
	int					bg;
	t_and_or			*and_or;
	struct s_cmdlist	*next;
}						t_cmdlist;

/*
**bg : 0 = forground, 1 = background
*/

typedef struct			s_io_list
{
	t_io_redirect		*node;
	struct s_io_list	*next;
}						t_io_list;

t_shell_var				g_var;

#endif
