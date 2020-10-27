/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 23:23:11 by afaraji           #+#    #+#             */
/*   Updated: 2020/01/14 23:23:26 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "21sh.h"
# include "readline.h"
# define STDIN	 0
# define STDOUT  1
# define STDERR  2

# define SPACE	-1			/* white space */
# define QUOTE	-2			/* '	*/
# define DQUOTE	-3			/* "	*/
# define SMCLN	-4			/* ;	*/
# define ANDLG	-5			/* &&	*/
# define ORLG	-6			/* ||	*/
# define PIP	-10			/* |	*/
# define BGJOB	-11			/* &	*/
# define ESCAPE	-12			/* \	*/
# define GRT	-20 		/* >	*/
# define GRTGRT	-21			/* >>	*/
# define SML	-22			/* <	*/
# define SMLSML	-30 		/* <<	*/

# define SMLAND	-24 		/* <&	*/
# define GRTAND	-25 		/* >&	*/
// # define SMLGRT	-26 		/* <>	*/
// # define CLOBBER -27 		/* >|	*/
// # define DSMLDASH -31 		/* <<-	*/

# define WORD	-42			/* word */

# define _OR(m,a,b,c,d,e) (m==a||m==b||m==c||m==d||m==e) ? 1 : 0

FILE	*ttt;

// <& (fd or file name) check if number => fd or string => filename only in aggr
// ' and " WORDs
// ls 2>&1 < kuhkj | cat -e  plan should read all command before exec


// cmd > file4 && cmd1 >> file3 || cmd2 7&> file2 & cmd3 1>&5  | cmd4 <&5 | cmd5 <<EOF | cmd6
// the line above return invalid read (doesn t stop at & BG)


// < cmd > file4 allo  && cmd1 >> file3 allo   | cmd2 7&> file2 allo ballo  | acmd3 1>&5 toto koko & cmd4 <&5 mimi | cmd5 <<EOF wowo ; cmd6 -p;

typedef struct					s_list_token
{
	int							type;
//	int							burned;	// if a node is read successful
	int							is_ok;	// for ' and " closed or not (1=closed)
	char						*data;
	struct s_list_token			*next;
	struct s_list_token			*prec;
}                               t_list_token;

typedef struct					s_alias
{
	char						*key;
	char						*sub;
	struct s_alias				*next;
}                               t_alias;

typedef struct				s_variable
{
	/*
	*	env == 0 --> part of env(eg. export).
	*	env == 1 --> part of set && only tmp.
	*	env == 2 --> part of set && permanent and read only.
	*/
	int						env;
	char					*key;
	char					*value;
	struct s_variable		*next;
}							t_variable;

typedef struct					s_proc
{
	pid_t						ppid;
	int							index;
	int							status;
	int							done;
	char						*str;
	struct s_proc				*next;
}                               t_proc;

typedef struct					s_shell_var
{
	int							errno;
	int							exit_status;
	int							sig;
	t_alias						*aliases;
	t_variable					*var;
	t_hist						*history;
	t_proc						*proc;
}								t_shell_var;

t_shell_var						g_var;

// ***************************************


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
	int						dependent;	// did i use it ? uselss
	t_simple_cmd			*left;
	struct s_pipe_seq		*right;
}							t_pipe_seq;

typedef struct				s_and_or
{
	int						dependent;	//(0';&' not dependt, 1 exec if $? == 0 '&&', 2 exec if $? != 0 '||')
	t_pipe_seq				*ast;
	struct s_and_or			*next;
}							t_and_or;

typedef struct				s_cmdlist
{
	int						bg;			// 0 = forground, 1 = background
	t_and_or				*and_or;
	struct s_cmdlist		*next;
}							t_cmdlist;

/*  ------- may change dep on the format needed for exec ------	*/

typedef struct				s_io_list
{
	t_io_redirect			*node;
	struct s_io_list		*next;
}							t_io_list;

/*	-----------------------------------------------------------	*/

int 			main_parse(char *line);
int				ft_exit(char **av);// aka exit();
void			exit_status(int status); // for commands
char			**env_to_tab(t_variable *var, int all);
char			**paths_from_env(void);
int				run_cmd(char **cmd);
int				builtins(char *cmd, char **av, char **env);
int				cd_builtin(char **av, char **env);
t_variable		*get_env(char *s, int typ);
char			*get_var_from_tab(char **env, char *str);
char			*ft_appendstr(char *s1, char *s2);
char			*ft_strsub_delimit(char *s, char c);
int				alias_infinit_loop(char *str, t_alias *aliases);
int				alias_sub(t_list_token *word, t_alias *aliases);
int				is_reserved(char *str);
void			insert_alias(char *key, char *sub);
void			get_aliases(void);
t_list_token	*__tokenize(char *str);
void			token_print(t_list_token *node);
void			parse_and_replace(t_list_token **cmd_token, t_list_token *node);
int				keywords_alias_sub(t_list_token **cmd_token);
char			*fetch_variables(char *key, int typ);
int				is_assword(char *str);
int				tilde_sub(t_list_token **cmd_token);
int				is_dollar(char *s);
int				end_dollar_word(char *s, int start);
char			*get_dollar_var(char *s, int start, int end);
char			*str_dollar_sub(char *str);
int				dollar_sub(t_list_token **cmd_token);
char			*get_pwd(char **env);
int				lexer(t_list_token **cmd_token);
void			add_proc(pid_t pid);
void			bg_jobs(void);

// ******************************************
// https://github.com/xopxop/21sh/blob/master/src/executor/redirects_great.c

/*
	https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_03
	https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form
	https://www.gnu.org/software/bash/manual/bash.html#Shell-Operation
	https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
	https://git.kernel.org/pub/scm/utils/dash/dash.git/tree/src

	https://catonmat.net/ftp/bash-redirections-cheat-sheet.pdf
*/

#endif
