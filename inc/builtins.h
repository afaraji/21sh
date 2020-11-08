/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:49:32 by sazouaka          #+#    #+#             */
/*   Updated: 2019/10/10 16:50:10 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "ft_21sh.h"

int		get_next_line(const int fd, char **line);
int		ft_cd(char *flag, char **env);
int		ft_cd_1(char *flag, char **env);
int		ft_cd_old(char **env);
int		ft_cd_home(char **env);
int		ft_setenv(char **flag, char **env);
int		ft_unsetenv(char **flag);
int		ft_echo(char **flag);
int		change_pwd(char *str1, char *str2);
void	free_tab(char **flag);
int		verify_type(char *file);
int		file_or_dir_link(char **file);
int		verify_type_1(char **file, struct stat st);
void	print_env(char **env);
int		ft_export(char **flag, char **env);
void	ft_export_2(char *key, char *value);
int		get_key_value(char **key, char **value, char *flag);
int		ft_pdenied(char *flag);
char	*ft_get_ld(char *cwd, char *flag);

#endif
