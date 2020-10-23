/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 23:23:11 by afaraji           #+#    #+#             */
/*   Updated: 2020/01/14 23:23:26 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "21sh.h"
# include "readline.h"
# include "parse.h"

void	    exit_status(int status);
int		    is_alldigit(char *str);
int	    	check_fd(int fd, int io);
int	    	do_heredoc(int fd_out, char *str);
int	    	do_redirect(t_io_redirect *io);
t_variable	*var_dup(t_variable *var);
int	       	do_assignement(t_cmd_prefix *pref, t_variable *head, int env);
int	    	do_prefix(t_cmd_prefix *prefix, t_variable *var, int env);
char    	**paths_from_env(void);
char    	*get_cmdpath(char *str);
int	    	env_tab_count(int all);
char    	**env_to_tab(t_variable *var, int all);
int	    	do_suffix(t_cmd_suffix *suffix);
int	    	do_simpleCmd(t_simple_cmd *cmd);
char    	**list_to_tab(t_l *list);
t_l     	*get_args(t_simple_cmd *cmd);
int	    	is_builtin(char *str);
t_l     	*var_sub(t_l *head);
char	    **get_arg_var_sub(t_simple_cmd *cmd);
int	    	exec_simple_cmd(t_simple_cmd *cmd);
int	    	exec_pipe(t_pipe_seq *cmd);
t_variable	*var_list_dup(t_variable *src);
void    	reset_in_out(int in, int out, int err);
int	    	exec_ast(t_pipe_seq *cmd, int bg);
int	    	execute(t_and_or *cmd, int bg);

#endif
