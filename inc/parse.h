/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 23:23:11 by afaraji           #+#    #+#             */
/*   Updated: 2020/10/31 20:38:55 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "ft_21sh.h"
# include "builtins.h"
# include "readline.h"
# include "parse.h"
# include "ast.h"
# include "exec.h"
# include "ft_free.h"

# define STDIN	0
# define STDOUT	1
# define STDERR	2
# define SETDFL	1
# define GETDFL	0
# define SPACE	-1
# define QUOTE	-2
# define DQUOTE	-3
# define SMCLN	-4
# define ANDLG	-5
# define ORLG	-6
# define PIP	-10
# define BGJOB	-11
# define ESCAPE	-12
# define GRT	-20
# define GRTGRT	-21
# define SML	-22
# define SMLSML	-30
# define SMLAND	-24
# define GRTAND	-25
# define WORD	-42

typedef struct				s_list_token
{
	int						type;
	char					*data;
	struct s_list_token		*next;
	struct s_list_token		*prec;
	int						is_ok;
}							t_list_token;

typedef struct				s_alias
{
	char					*key;
	char					*sub;
	struct s_alias			*next;
}							t_alias;

typedef struct				s_variable
{
	int						env;
	char					*key;
	char					*value;
	struct s_variable		*next;
}							t_variable;
/*
**env == 0 --> part of env(eg. export).
**env == 1 --> part of set && only tmp.
**env == 2 --> part of set && permanent and read only.
*/

typedef struct				s_proc
{
	pid_t					ppid;
	int						index;
	int						status;
	int						done;
	char					*str;
	struct s_proc			*next;
}							t_proc;

typedef struct				s_shell_var
{
	int						errno;
	int						exit_status;
	int						sig;
	t_alias					*aliases;
	t_variable				*var;
	t_hist					*history;
	t_proc					*proc;
}							t_shell_var;

typedef struct				s_io_redirect
{
	int						redirect_type;
	int						io_num;
	char					*filename;
}							t_io_redirect;

typedef struct				s_cmd_suffix
{
	t_io_redirect			*io_redirect;
	char					*word;
	struct s_cmd_suffix		*suffix;
}							t_cmd_suffix;

typedef struct				s_cmd_prefix
{
	t_io_redirect			*io_redirect;
	t_variable				*ass_word;
	struct s_cmd_prefix		*prefix;
}							t_cmd_prefix;

typedef struct				s_simple_cmd
{
	char					*word;
	char					*name;
	t_cmd_prefix			*prefix;
	t_cmd_suffix			*suffix;
}							t_simple_cmd;

typedef struct				s_pipe_seq
{
	t_simple_cmd			*left;
	struct s_pipe_seq		*right;
}							t_pipe_seq;

typedef struct				s_and_or
{
	int						dependent;
	t_pipe_seq				*ast;
	struct s_and_or			*next;
}							t_and_or;

/*
**dependent : (0';&' not dependt, 1 exec if $? == 0 '&&',
**2 exec if $? != 0 '||')
*/

typedef struct				s_cmdlist
{
	int						bg;
	t_and_or				*and_or;
	struct s_cmdlist		*next;
}							t_cmdlist;

/*
**bg : 0 = forground, 1 = background
*/

typedef struct				s_io_list
{
	t_io_redirect			*node;
	struct s_io_list		*next;
}							t_io_list;

int							main_parse(char *line);
int							ft_or(int m, int a, int b, int c);
int							ft_print(int fd, char *format, ...);
int							ft_exit(char **av);
void						exit_status(int status);
char						**env_to_tab(t_variable *var, int all);
char						**paths_from_env(void);
int							run_cmd(char **cmd);
int							builtins(char *cmd, char **av, char **env);
int							cd_builtin(char **av, char **env);
t_variable					*get_env(char *s, int typ);
char						*get_var_from_tab(char **env, char *str);
char						*ft_appendstr(char *s1, char *s2);
char						*ft_strsub_delimit(char *s, char c);
int							alias_infinit_loop(char *str, t_alias *aliases);
int							alias_sub(t_list_token *word, t_alias *aliases);
int							is_reserved(char *str);
void						insert_alias(char *key, char *sub);
void						get_aliases(void);
t_list_token				*ft_tokenize(char *str);
void						token_print(t_list_token *node);
void						parse_and_replace(t_list_token **cmd_token,
							t_list_token *node);
int							keywords_alias_sub(t_list_token **cmd_token);
char						*fetch_variables(char *key, int typ);
int							is_assword(char *str);
int							tilde_sub(t_list_token **cmd_token);
int							is_dollar(char *s);
int							end_dollar_word(char *s, int start);
char						*get_dollar_var(char *s, int start, int end);
char						*str_dollar_sub(char *str);
int							dollar_sub(t_list_token **cmd_token);
char						*get_pwd(char **env);
int							lexer(t_list_token **cmd_token);
void						add_proc(pid_t pid);
void						bg_jobs(void);

#endif
