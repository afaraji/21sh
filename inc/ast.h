/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 23:23:11 by afaraji           #+#    #+#             */
/*   Updated: 2020/01/14 23:23:26 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "ft_21sh.h"

int				is_op(char *str, int i);
void			token_print(t_list_token *node);
void			token_print_inverse(t_list_token *node);
char			*tokentoa(int token);
t_list_token	*add_quote(int *index, char *str);
t_list_token	*add_dquote(int *index, char *str);
t_list_token	*add_space(int *index, char *str);
t_list_token	*add_escape(int *index, char *str);
t_list_token	*add_op(int *index, int op);
t_list_token	*add_word_int(int *index, char *str);
t_list_token	*tokenize(char *str, int *i);
t_list_token	*ft_tokenize(char *str);
void			print_io_redirect(t_io_redirect *head);
void			print_cmdprefix(t_cmd_prefix *head);
void			print_cmdsuffix(t_cmd_suffix *head);
void			print_simple_cmd(t_simple_cmd *cmd);
int				is_valid_word(char *s);
int				is_valid_file(char *file, t_list_token *node);
char			*io_file(t_list_token **cmd, t_list_token **end, int *r_type);
char			*io_here(t_list_token **cmd, t_list_token **end, int *r_type);
t_io_redirect	*io_redirect(t_list_token **cmd, t_list_token **end);
t_variable		*ass_word(t_list_token **cmd, t_list_token **end);
t_cmd_prefix	*cmd_prefix(t_list_token **cmd, t_list_token **end);
char			*cmd_word(t_list_token **cmd, t_list_token **end);
t_cmd_suffix	*cmd_suffix(t_list_token **cmd, t_list_token **end);
char			*cmd_name(t_list_token	**cmd, t_list_token **end);
t_simple_cmd	*get_simple_cmd(t_list_token *start, t_list_token *end);
t_pipe_seq		*ast(t_list_token *tokens);
t_list_token	*list_sub(t_list_token *start, t_list_token *end);
void			print_tokenlist(t_pipe_seq *ast);
void			print_andor(t_cmdlist *list);
void			free_token_node(t_list_token **todel);
void			join_nodes(t_list_token *dst, t_list_token *todel);
void			join_words(t_list_token *token);
int				verify_tokens(t_list_token *token);
t_and_or		*get_andor_list(t_list_token *strt, int dep, t_list_token *end);
t_and_or		*token_split_andor(t_list_token *start, t_list_token *end);
t_cmdlist		*token_split_sep_op(t_list_token *tokens);
int				need_append(t_list_token *tokens);
char			*here_doc_string(char *word);
void			here_doc(t_list_token *head);
int				main_parse(char *line);
t_list_token	*get_last_node_toappend(t_list_token *tokens);
char			*ft_4strjoin(char *s1, char *s2, char *s3, char *s4);

#endif
