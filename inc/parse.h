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
# define BUILTINS	"echo|export|cd|setenv|unsetenv|env|exit|alias|unalias"
# define RSRVDWORD	"case|do|done|elif|else|esac|fi|for|if|in|then|until|while"

int				main_parse(char *line);
int				ft_or(int m, int a, int b, int c);
int				ft_print(int fd, char *format, ...);
int				ft_exit(char **av);
void			exit_status(int status);
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
t_list_token	*ft_tokenize(char *str);
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
int				ft_alias(char **av);
int				ft_unalias(char **av);
void			ft_signal(void);
void			get_ppid_list(void);
int				init_shell(char **env);
t_hist			*create_history(void);
char			*delete_escape(char *str);

#endif
