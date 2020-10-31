/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:35:14 by afaraji           #+#    #+#             */
/*   Updated: 2020/10/31 20:37:14 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FREE_H
# define FT_FREE_H
# include "parse.h"

void		free_tokens(t_list_token *tokens);
void		free_cmd_list(t_cmdlist *list);
void		free_l(t_l *list);
void		free_tab(char **av);
void		free_list(t_l *head);

#endif
