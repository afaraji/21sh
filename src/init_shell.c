/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:00:18 by sazouaka          #+#    #+#             */
/*   Updated: 2020/10/29 23:56:26 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

t_hist		*create_history(void)
{
	char	*file_str;
	t_hist	*his_list;
	int		fd;
	int		i;

	his_list = NULL;
	if ((fd = open(HIST_FILE, O_RDONLY | O_CREAT, 0600)) == -1)
	{
		ft_print(STDERR, "couldn't create nor find history list.\n");
		return (NULL);
	}
	i = 1;
	while (get_next_line(fd, &file_str) == 1)
	{
		get_his_list(file_str, &his_list, i++);
		ft_strdel(&file_str);
	}
	close(fd);
	return (his_list);
}

t_variable	*get_env(char *s, int typ)
{
	t_variable	*node;
	int			i;

	i = 0;
	node = (t_variable *)malloc(sizeof(t_variable));
	node->next = NULL;
	node->env = typ;
	while (s && s[i] && s[i] != '=')
		i++;
	node->key = ft_strsub(s, 0, i);
	node->value = ft_strdup(&s[i + 1]);
	node->next = NULL;
	return (node);
}

t_variable	*get_setvar(void)
{
	char		*tmp1;
	char		*tmp2;
	t_variable	*head;

	head = get_env("!=0", 2);
	head->next = get_env("#=0", 2);
	tmp1 = ft_itoa(getpid());
	tmp2 = ft_strjoin("$=", tmp1);
	head->next->next = get_env(tmp2, 2);
	free(tmp1);
	free(tmp2);
	head->next->next->next = get_env("?=0", 2);
	return (head);
}

t_variable	*get_set(char **env)
{
	t_variable	*head;
	t_variable	*node;
	int			i;

	head = get_setvar();
	node = head;
	while (node->next)
		node = node->next;
	i = 0;
	while (env && env[i])
	{
		node->next = get_env(env[i], 0);
		node = node->next;
		i++;
	}
	return (head);
}

int			init_shell(char **env)
{
	g_var = (t_shell_var){0, 0, 0, NULL, NULL, NULL, NULL, NULL};
	g_var.var = get_set(env);
	g_var.history = create_history();
	get_ppid_list();
	return (0);
}
