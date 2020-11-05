/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:35:14 by afaraji           #+#    #+#             */
/*   Updated: 2020/10/31 20:54:20 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FREE_H
# define FT_FREE_H
# include "ft_21sh.h"

void	free_tokens(t_list_token *tokens);
void	free_cmd_list(t_cmdlist *list);
void	free_and_or_list(t_and_or *list);
void	free_ast(t_pipe_seq *ast);
void	free_simple_cmd(t_simple_cmd *cmd);
void	free_prefix(t_cmd_prefix *pref);
void	free_suffix(t_cmd_suffix *suff);
void	free_l(t_l *list);
void	free_tab(char **av);
void	free_list(t_l *head);
void	free_t_var(t_variable *list);
void	free_g_var(void);
void	free_aliases(t_alias **alias);
void	free_history_list(t_hist *list);
void	free_file_dir(char **file_dir);

#endif
