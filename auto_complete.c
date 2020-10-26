/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 19:33:46 by sazouaka          #+#    #+#             */
/*   Updated: 2020/10/02 19:33:48 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "parse.h"

void			print_tab(char **tabl)
{
	int		i;

	i = 0;
	while (tabl[i])
	{
		ft_putchar('\n');
		ft_putstr(tabl[i]);
		i++;
	}
}

int				get_path_1(char *str)
{
	int		index;

	index = ft_strlen(str) - 1;
	while (index >= 0)
	{
		if (str[index] == '/')
			break ;
		index--;
	}
	return (index);
}

char			*get_path_2(char **str, int i)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strsub(*str, 0, i + 1);
	if (tmp1[0] == '/' || (tmp1[0] == '.' && tmp1[1] == '/'))
	{
		free(*str);
		return (tmp1);
	}
	else
	{
		tmp2 = ft_strjoin("./", tmp1);
		free(tmp1);
		return (tmp2);
	}
}

char			*get_path(char *str)
{
	int		i;

	i = get_path_1(str);
	if (i == -1)
	{
		if (!ft_strcmp(str, ""))
		{
			free(str);
			return (ft_strdup("./"));
		}
	}
	else if (i != -1)
		return (get_path_2(&str, i));
	return (str);
}

char			*get_to_cmp(char *str)
{
	int		i;
	int		j;
	char	*file_to_find;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '/')
			j = i + 1;
		i++;
	}
	file_to_find = ft_strsub(str, j, i);
	return (file_to_find);
}

t_l				*names_list(char *str)
{
	t_l	*node;

	node = (t_l *)malloc(sizeof(t_l));
	node->data = ft_strdup(str);
	node->next = NULL;
	return (node);
}

t_l	*get_var_list(char *str, t_l *head)
{
	t_l	*node;
	char			*tmp;

	if (!head)
	{
		head = (t_l *)malloc(sizeof(t_l));
		tmp = ft_strdup(str);
		head->data = ft_strjoin("$", tmp);
		free(tmp);
		head->next = NULL;
		return (head);
	}
	node = head;
	while (node->next)
		node = node->next;
	node->next = (t_l *)malloc(sizeof(t_l));
	node = node->next;
	tmp = ft_strdup(str);
	node->data = ft_strjoin("$", tmp);
	free(tmp);
	node->next = NULL;
	return (head);
}

int				get_node_sum(t_l *head)
{
	int				sum;
	t_l	*node;

	sum = 0;
	node = head;
	while (node)
	{
		sum++;
		node = node->next;
	}
	return (sum);
}

t_l	*sort_list(t_l *head)
{
	t_l	*node1;
	t_l	*node2;
	char			*tmp;

	node1 = head;
	while (node1->next)
	{
		node2 = node1->next;
		while (node2)
		{
			if (ft_strcmp(node1->data, node2->data) > 0)
			{
				tmp = node1->data;
				node1->data = node2->data;
				node2->data = tmp;
			}
			node2 = node2->next;
		}
		node1 = node1->next;
	}
	return (head);
}

char			**tab_from_list(t_l *head)
{
	t_l	*node;
	char			**tabl;
	int				sum;

	node = head;
	sum = get_node_sum(head);
	tabl = (char **)malloc(sizeof(char *) * (sum + 1));
	node = head;
	sum = 0;
	while (node)
	{
		if (!(node->next) || ft_strcmp(node->data, node->next->data))
		{
			tabl[sum] = ft_strdup(node->data);
			sum++;
		}
		node = node->next;
	}
	tabl[sum] = NULL;
	return (tabl);
}

void			ft_free_list(t_l *head)
{
	t_l	*tmp1;
	t_l	*tmp2;

	tmp1 = head;
	while (tmp1)
	{
		tmp2 = tmp1;
		tmp1 = tmp1->next;
		free(tmp2->data);
		free(tmp2);
	}
}

char			**var_search(char *str)
{
	t_variable		*var;
	t_l	*var_list;
	char			**var_tab;

	var = g_var.var;
	var_list = NULL;
	while (var)
	{
		if (!ft_strncmp(str, var->key, ft_strlen(str)))
			var_list = get_var_list(var->key, var_list);
		var = var->next;
	}
	var_tab = tab_from_list(var_list);
	ft_free_list(var_list);
	return (var_tab);
}

t_l				*matched_f_d(DIR *d, char *str)
{
	struct dirent	*dir;
	char			*tmp;
	t_l				*f_d_list = NULL;
	t_l				*node;

	while ((dir = readdir(d)))
	{
		tmp = ft_strjoin("./", dir->d_name);
		if (verify_type(tmp) == 1)
		{
			free(tmp);
			tmp = ft_strjoin(dir->d_name, "/");
		}
		else
		{
			free(tmp);
			tmp = ft_strdup(dir->d_name);
		}
		if (!ft_strcmp("", str) || !ft_strncmp(dir->d_name, str, ft_strlen(str)))
		{
			if (!f_d_list)
			{
				f_d_list = names_list(tmp);
				node = f_d_list;
			}
			else
			{
				node->next = names_list(tmp);
			}
		}
	}
	return (f_d_list);
}

t_l	*matched_files_dirs(char *str)
{
	DIR	*d;
	t_l	*files_dirs_list;

	files_dirs_list = NULL;
	d = opendir(".");
	if (d != NULL)
	{
		files_dirs_list = matched_f_d(d, str);
	}
	closedir(d);
	return (files_dirs_list);
}

t_l				*f_d_search(char *path, char *d_name, char *cmp, char *f_d)
{
	t_l		*list;

	list = NULL;
	if (path[0] == '.')
	{
		if (ft_strcmp(d_name, ".") && ft_strcmp(d_name, ".."))
		{
			if ((!ft_strcmp("", cmp) ||
			!ft_strncmp(d_name, cmp, ft_strlen(cmp))))
			{
				list = names_list(f_d);
			}
			free(f_d);
			return (list);
		}
	}
	else
	{
		if ((!ft_strcmp("", cmp) || !ft_strncmp(d_name, cmp, ft_strlen(cmp))) && d_name[0] != '.')
			list = names_list(f_d);
		free(f_d);
		return (list);
	}
	return (NULL);
}

char			*files_dirs_search_3(char *d_name, char *path)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	if (!(ft_strcmp(path, ".")))
	{
		tmp1 = ft_strjoin(path, "/");
		tmp2 = ft_strjoin(tmp1, d_name);
		free(tmp1);
	}
	else
		tmp2 = ft_strjoin(path, d_name);
	if (verify_type(tmp2) == 1)
	{
		free(tmp2);
		tmp2 = ft_strjoin(d_name, "/");
	}
	else
	{
		free(tmp2);
		tmp2 = ft_strdup(d_name);
	}
	return (tmp2);
}

char			**files_dirs_search_2(char *path)
{
	char			**dir_tab;
	t_l	*files_dirs_list;

	files_dirs_list = matched_files_dirs(path);
	if (files_dirs_list)
	{
		dir_tab = tab_from_list(sort_list(files_dirs_list));
		ft_free_list(files_dirs_list);
	}
	else
	{
		dir_tab = (char **)malloc(sizeof(char *) * 1);
		dir_tab[0] = NULL;
	}
	return (dir_tab);
}

char			**files_dirs_search_1(char *path, char *to_cmp, DIR *d)
{
	struct dirent	*dir;
	char			*file_dir;
	char			**dir_tab;
	t_l				*files_dirs_list;
	t_l				*node;

	files_dirs_list = NULL;
	file_dir = NULL;
	while ((dir = readdir(d)))
	{
		file_dir = files_dirs_search_3(dir->d_name, path);
		if (!files_dirs_list)
		{
			files_dirs_list = f_d_search(path, dir->d_name, to_cmp, file_dir);
			node = files_dirs_list;
		}
		else
		{
			node->next = f_d_search(path, dir->d_name, to_cmp, file_dir);
			if (node->next)
			{
				node = node->next;
			}
		}
	}
	closedir(d);
	if (files_dirs_list)
	{
		dir_tab = tab_from_list(sort_list(files_dirs_list));
		ft_free_list(files_dirs_list);
	}
	else
	{
		dir_tab = (char **)malloc(sizeof(char *) * 1);
		dir_tab[0] = NULL;
	}
	return (dir_tab);
}

char			**files_dirs_search(char *str, int i)
{
	DIR				*d;
	char			*to_cmp;
	char			*path;
	t_l	*files_dirs_list;
	char			**dir_tab;

	path = get_path(str);
	to_cmp = get_to_cmp(str);
	files_dirs_list = NULL;
	d = opendir(path);
	if (d != NULL)
	{
		return (files_dirs_search_1(path, to_cmp, d));
	}
	else if (d == NULL)
	{
		return (files_dirs_search_2(path));
	}
	return (NULL);
}

t_l	*get_cmd_list_1(char *str, t_l *head)
{
	t_l	*node;

	if (!head)
	{
		head = (t_l *)malloc(sizeof(t_l));
		head->data = ft_strdup(str);
		head->next = NULL;
		return (head);
	}
	node = head;
	while (node->next)
		node = node->next;
	node->next = (t_l *)malloc(sizeof(t_l));
	node = node->next;
	node->data = ft_strdup(str);
	node->next = NULL;
	return (head);
}

t_l	*search_builtin(char *str)
{
	int				i;
	t_l	*head;
	char			*builtins_list[] = {"cd", "echo", "export", "env",
						"exit", "setenv", "unsetenv", NULL};

	i = 0;
	head = NULL;
	while (builtins_list[i])
	{
		if (!ft_strncmp(builtins_list[i], str, ft_strlen(str)))
			head = get_cmd_list_1(builtins_list[i], head);
		i++;
	}
	return (head);
}

int				get_path_value(char ***str)
{
	t_variable	*var;

	var = g_var.var;
	while (var)
	{
		if (!ft_strcmp(var->key, "PATH"))
		{
			*str = ft_strsplit(var->value, ':');
			return (1);
		}
		var = var->next;
	}
	return (0);
}

void			cmd_path_1(char **tmp, char ***cmd_paths)
{
	int	i;

	i = 0;
	while (tmp[i])
		i++;
	*cmd_paths = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tmp[i])
	{
		(*cmd_paths)[i] = ft_strjoin(tmp[i], "/");
		free(tmp[i]);
		i++;
	}
	(*cmd_paths)[i] = NULL;
}

int				cmd_path(t_l *cmd_list, char ***cmd_tab, char ***cmd_paths)
{
	char	**tmp;

	tmp = NULL;
	get_path_value(&tmp);
	if (tmp == NULL)
	{
		if (cmd_list)
			*cmd_tab = tab_from_list(sort_list(cmd_list));
		else
		{
			*cmd_tab = (char **)malloc(sizeof(char *) * 1);
			(*cmd_tab)[0] = NULL;
		}
		return (1);
	}
	else if (tmp != NULL)
	{
		cmd_path_1(tmp, cmd_paths);
		return (2);
	}
	return (0);
}

void			get_cmd_list(t_l **cmd_list, char **cmd_paths, char *str)
{
	int				i;
	DIR				*d;
	struct dirent	*dir;

	i = 0;
	while (cmd_paths[i])
	{
		d = opendir(cmd_paths[i]);
		if (d)
		{
			while ((dir = readdir(d)))
			{
				if (!ft_strncmp(str, dir->d_name, ft_strlen(str))
				&& ft_strcmp(dir->d_name, ".")
				&& ft_strcmp(dir->d_name, ".."))
				{
					*cmd_list = get_cmd_list_1(dir->d_name, *cmd_list);
				}
			}
		}
		i++;
	}
	if (d)
		closedir(d);
}

char			**cmd_search(char *str)
{
	char			**cmd_paths;
	t_l	*cmd_list;
	char			**cmd_tab;

	cmd_tab = NULL;
	cmd_list = search_builtin(str);
	if (cmd_path(cmd_list, &cmd_tab, &cmd_paths) == 1)
		return (cmd_tab);
	get_cmd_list(&cmd_list, cmd_paths, str);
	if (!cmd_list)
	{
		cmd_tab = (char **)malloc(sizeof(char *) * 1);
		cmd_tab[0] = NULL;
	}
	else
		cmd_tab = tab_from_list(sort_list(cmd_list));
	free(cmd_list);
	return (cmd_tab);
}

int				is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (2);
		i++;
	}
	return (0);
}

char			**completion_split_1(char **table)
{
	char	**tmp;
	int		i;

	i = 0;
	while (table[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (table[i])
	{
		tmp[i] = ft_strdup(table[i]);
		i++;
	}
	tmp[i] = ft_strdup("");
	tmp[i + 1] = NULL;
	return (tmp);
}

char			**completion_split(char *line)
{
	char	**table;

	if (!ft_strcmp(line, ""))
	{
		table = (char **)malloc(sizeof(char *) * 2);
		table[0] = ft_strdup("");
		table[1] = NULL;
		return (table);
	}
	table = ft_strsplit(line, ' ');
	if (line[ft_strlen(line) - 1] == ' ')
	{
		return (completion_split_1(table));
	}
	return (table);
}

char			*completed_line(char *line, char *str)
{
	int		i;
	char	*left;
	char	*tmp;

	i = ft_strlen(line) - 1;
	while (i >= 0)
	{
		if (line[i] == '/' || line[i] == ' ')
			break ;
		i--;
	}
	left = ft_strsub(line, 0, i + 1);
	tmp = ft_strjoin(left, str);
	free(left);
	free(line);
	return (tmp);
}

t_completion	*get_completion_var(void)
{
	t_completion	*compl;

	if (!(compl = (t_completion *)malloc(sizeof(t_completion))))
		return (NULL);
	compl->total_words = 0;
	compl->str_max_len = 0;
	return (compl);
}

void			print_result_1(t_completion *compl, char **t, t_line *line)
{
	int i;

	compl->word_per_line = line->col / compl->str_max_len;
	compl->lines_to_print = compl->total_words / compl->word_per_line;
	compl->words_to_print = (line->row - 1) * compl->word_per_line;
	i = 0;
	while (compl->total_words)
	{
		ft_putstr(t[i]);
		compl->space = compl->str_max_len - ft_strlen(t[i]);
		while (compl->space)
		{
			ft_putchar(' ');
			compl->space--;
		}
		compl->total_words--;
		compl->words_to_print--;
		if (compl->total_words
		&& (compl->words_to_print % compl->word_per_line == 0))
			ft_putchar('\n');
		(i)++;
	}
}

void			print_result(char **t, t_line *line)
{
	t_completion	*compl;

	compl = get_completion_var();
	while (t[compl->total_words])
	{
		if (ft_strlen(t[compl->total_words]) > compl->str_max_len)
		{
			compl->str_max_len = ft_strlen(t[compl->total_words]) + 3;
			compl->total_words++;
		}
		else
			compl->total_words++;
	}
	print_result_1(compl, t, line);
}

int				get_home_path(char **str)
{
	t_variable	*var;
	char		*tmp;

	var = g_var.var;
	while (var)
	{
		if (!ft_strcmp(var->key, "HOME"))
		{
			tmp = ft_strsub(*str, 1, ft_strlen(*str));
			free(*str);
			*str = ft_strjoin(var->value, tmp);
			return (1);
		}
		var = var->next;
	}
	return (0);
}

char			**auto_completion_1(t_line *line)
{
	char	**result;
	char	**splited_line;
	int		i;

	splited_line = completion_split(line->str);
	i = 0;
	while (splited_line[i + 1])
		i++;
	if (splited_line[i][0] == '~' && splited_line[i][1] == '/')
		get_home_path(&splited_line[i]);
	if (splited_line[i][0] == '$')
	{
		if (splited_line[i][1] == '{')
			result = var_search(splited_line[i] + 2);
		else
			result = var_search(splited_line[i] + 1);
	}
	else if (i == 0 && splited_line[0][0] == '.')
		result = files_dirs_search(splited_line[0], i);
	else if (i != 0 || is_path(splited_line[i]) != 0)
		result = files_dirs_search(splited_line[i], i);
	else
		result = cmd_search(splited_line[0]);
	return (result);
}

int				auto_completion(t_line *line)
{
	char	**result;
	int		j;

	result = auto_completion_1(line);
	if (result[0] == NULL)
		return (0);
	j = 0;
	while (result && result[j + 1])
		j++;
	if (j == 0)
	{
		line->str = completed_line(line->str, result[0]);
		display_line(line);
		move_curs_right(line);
		return (1);
	}
	else
	{
		ft_putchar('\n');
		print_result(result, line);
		return (2);
	}
	return (0);
}
