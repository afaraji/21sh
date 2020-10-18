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
# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <signal.h>

# define PATH_D "#PATH_D=#"
# define NEXT_CHAR(i) (ft_isalnum(i) || i == '_')
# define BUFF_CHAR(c) (c&&c!=39&&c!=34&&c!='$'&&c!='~'&&c!=' '&&c!='\t')

extern int		g_sign;

typedef struct		s_lst
{
	char			*name;
	char			*content;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_point
{
	int				i;
	int				j;
}					t_point;

int					get_next_line(const int fd, char **line);
char				*ft_parse(char *buff, t_lst *head);
t_lst				*ft_env(char **env);
char				**ft_path(t_lst *head);
void				ft_exec(char **flag, t_lst *env_list);
void				ft_printlist(t_lst *list);
int	   				ft_cd(char *flag);
int	    			ft_cd_1(char *flag);
int					ft_cd_old(char **env);
int 				ft_cd_home(char **env);
int					ft_setenv(char **flag);
int					ft_unsetenv(char **flag);
int					ft_echo(char **flag);
char				**env_tab_(t_lst *head);
int					change_pwd(char *str1, char *str2);
void				free_tab(char **flag);
int					verify_type(char *file);
char				*get_var_val(char *str, int *end, t_lst *head);
int					ft_parse_len(char *buff, t_lst *head);
void				free_list(t_lst *head);
void				main_2(char *tmp, t_lst *env_list);
int					single_quote_1(char *buff, char *str, t_point *ps);
int					double_quote_1(char *buf, char *s, t_lst *head, t_point *p);
void				ft_dolar(char *buff, char *str, t_lst *head, t_point *ps);
void				get_str(char *buff, char *str, t_point *ps);
void				ft_len(int *i, int *len);
void    			print_env(char **env);
int					ft_setenv(char **flag);
int					ft_export(char **flag, char **env);
void			    ft_export_2(char *key, char *value);
int     			get_key_value(char **key, char **value, char *flag);

#endif
