
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazouaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 19:33:46 by sazouaka          #+#    #+#             */
/*   Updated: 2020/10/02 19:33:48 by sazouaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "readline.h"
#include "parse.h"

void	print_tab(char **tabl)
{
	int		i;

	i = 0;
	while (tabl[i])
	{
		fprintf(ttyfd, "%s\n", tabl[i]);
		//ft_putchar('\n');
		//ft_putstr(tabl[i]);
		i++;
	}
}

void	print_list(t_simple_lst *head)
{
	t_simple_lst	*node;
	int		i;

	node = head;
	i = 1;
	while (node)
	{
		fprintf(ttyfd, "%d : %s\n", i , node->data);
		i++;
		node = node->next;
	}
}

char    *get_path(char *str)
{
	int		i;
	char    *tmp1;
	char    *tmp2;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == '/')
			break;
		i--;
	}
	if (i == -1 && !ft_strcmp(str, ""))
		return (ft_strdup("."));
	else if (i != -1)
	{
		tmp1 = ft_strsub(str, 0, i + 1);
		if (tmp1[0] == '/' || (tmp1[0] == '.' && tmp1[1] == '/'))
			return (tmp1);
		else
		{
			tmp2 = ft_strjoin("./", tmp1);
			free(tmp1);
			return (tmp2);
		}
	}
	return (str);
}

char    *get_to_cmp(char *str)
{
	int i;
	int j;
	char    *file_to_find;
	
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

t_simple_lst   *names_list(char *str, t_simple_lst *head)
{
	t_simple_lst	*node;

	if (!head)
	{
		head = (t_simple_lst *)malloc(sizeof(t_simple_lst));
		head->data = ft_strdup(str);
		head->next = NULL;
		return(head);
	}
	node = head;
	while (node->next)
		node = node->next;
	node->next = (t_simple_lst *)malloc(sizeof(t_simple_lst));
	node = node->next;
	node->data = ft_strdup(str);
	node->next = NULL;
	return (head);
}

t_simple_lst   *get_var_list(char *str, t_simple_lst *head)
{
	t_simple_lst	*node;
	char			*tmp;

	if (!head)
	{
		head = (t_simple_lst *)malloc(sizeof(t_simple_lst));
		tmp = ft_strdup(str);
		head->data = ft_strjoin("$", tmp);
		free(tmp);
		head->next = NULL;
		return(head);
	}
	node = head;
	while (node->next)
		node = node->next;
	node->next = (t_simple_lst *)malloc(sizeof(t_simple_lst));
	node = node->next;
	tmp = ft_strdup(str);
	node->data = ft_strjoin("$", tmp);
	free(tmp);
	node->next = NULL;
	return (head);
}

int	get_node_sum(t_simple_lst *head)
{
	int		sum;
	t_simple_lst	*node;

	sum = 0;
	node = head;
	while (node)
	{
		sum++;
		node = node->next;
	}
	return (sum);
}

t_simple_lst	*sort_list(t_simple_lst *head)
{
	t_simple_lst	*node1;
	t_simple_lst	*node2;
	char	*tmp;

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

char	**tab_from_list(t_simple_lst *head)
{
	t_simple_lst	*node;
	char	**tabl;
	int		sum;


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
void	ft_free_list(t_simple_lst *head)
{
	t_simple_lst	*tmp1;
	t_simple_lst	*tmp2;

	tmp1 = head;
	while (tmp1)
	{
		tmp2 = tmp1;
		tmp1 = tmp1->next;
		free(tmp2->data);
		free(tmp2);
	}
}


char	**var_search(char *str)
{
	t_variable	*var;
	t_simple_lst		*var_list;
	char		**var_tab;

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
	return(var_tab);
}

t_simple_lst   *matched_files_dirs(char *str, t_simple_lst *head)
{
	DIR     *d;
	struct  dirent *dir;
	t_simple_lst   *files_dirs_list;

	files_dirs_list = NULL;
	d = opendir(".");
	if (d != NULL)
	{
		while ((dir = readdir(d)))
		{
			if (!ft_strcmp("", str) || !ft_strncmp(dir->d_name, str, ft_strlen(str)))
				files_dirs_list = names_list(dir->d_name, files_dirs_list);
		}
	}
	closedir(d);
	return(files_dirs_list);
}

char	**files_dirs_search(char *str, int i)
{
	DIR     *d;
	struct  dirent *dir;
	char    *to_cmp;
	char    *path;
	t_simple_lst   *files_dirs_list;
	char    **dir_tab;
	struct  stat sb;
	
	path = get_path(str);
	to_cmp = get_to_cmp(str);
	files_dirs_list = NULL;
	d = opendir(path);
	if (d != NULL)
	{
		while ((dir = readdir(d)))
		{
			if (path[0] == '.')
			{
				if (ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, ".."))
				{
					if ((!ft_strcmp("", to_cmp) || !ft_strncmp(dir->d_name, to_cmp, ft_strlen(to_cmp))))
						files_dirs_list = names_list(dir->d_name, files_dirs_list);
					else if (i == 0 && (stat(dir->d_name, &sb) == 0 && sb.st_mode & S_IXUSR))
						files_dirs_list = names_list(dir->d_name, files_dirs_list);
				}
			}
			else
			{
				if ((!ft_strcmp("", to_cmp) || !ft_strncmp(dir->d_name, to_cmp, ft_strlen(to_cmp))) && dir->d_name[0] != '.')
					files_dirs_list = names_list(dir->d_name, files_dirs_list);
			}
			
			
		}
		closedir(d);
		if (files_dirs_list)
			dir_tab = tab_from_list(sort_list(files_dirs_list));
		else
		{
			dir_tab = (char **)malloc(sizeof(char *) * 1);
			dir_tab[0] = NULL;
		}
	}
	else if (d == NULL)
	{
		files_dirs_list = matched_files_dirs(str, files_dirs_list);
		if (files_dirs_list)
			dir_tab = tab_from_list(sort_list(files_dirs_list));
		else
		{
			dir_tab = (char **)malloc(sizeof(char *) * 1);
			dir_tab[0] = NULL;
		}
	}
	if (files_dirs_list)
		ft_free_list(files_dirs_list);
	return(dir_tab);
}


t_simple_lst	*get_cmd_list(char *str, t_simple_lst *head)
{
	t_simple_lst	*node;

	if (!head)
	{
		head = (t_simple_lst *)malloc(sizeof(t_simple_lst));
		head->data = ft_strdup(str);
		head->next = NULL;
		return(head);
	}
	node = head;
	while (node->next)
		node = node->next;
	node->next = (t_simple_lst *)malloc(sizeof(t_simple_lst));
	node = node->next;
	node->data = ft_strdup(str);
	node->next = NULL;
	return (head);
}

t_simple_lst	*search_builtin(char *str)
{
	int i;
	t_simple_lst	*head;
	char *builtins_list[] = {"cd", "echo", "export", "env",
						"exit", "setenv", "unsetenv", NULL};

	i = 0;
	head = NULL;
	while (builtins_list[i])
	{
		if(!ft_strncmp(builtins_list[i], str, ft_strlen(str)))
			head = get_cmd_list(builtins_list[i], head);
		i++;
	}
	return (head);
}

char	**cmd_search(char *str)
{	
	t_variable		*var;
	char			**cmd_paths;
	char			**tmp;
	int				i;
	DIR				*d;
	struct dirent	*dir;
	t_simple_lst			*cmd_list;
	char			**cmd_tab;

	cmd_list = search_builtin(str);
	var = g_var.var;
	while (var)
	{
		if (!ft_strcmp(var->key, "PATH"))
		{
			tmp = ft_strsplit(var->value, ':');
			break;
		}
		var = var->next;
	}
	i = 0;
	while (tmp[i])
		i++;
	cmd_paths = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tmp[i])
	{
		cmd_paths[i] = ft_strjoin(tmp[i], "/");
		i++;
	}
	cmd_paths[i] = NULL;
	i = 0;
	while (cmd_paths[i])
	{
		d = opendir(cmd_paths[i]);
		if (d)
		{
			while ((dir = readdir(d)))
			{
				if (!ft_strncmp(str, dir->d_name, ft_strlen(str))
					&& ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, ".."))
				{	
					cmd_list = get_cmd_list(dir->d_name, cmd_list);
				}
			}
		}
		i++;
	}
	closedir(d);
	if (!cmd_list)
	{
		cmd_tab = (char **)malloc(sizeof(char *) * 1);
		cmd_tab[0] = NULL;
	}
	else
		cmd_tab = tab_from_list(sort_list(cmd_list));
	free(cmd_list);
	return(cmd_tab);
}

int is_path(char *str)
{
	int i;

	i = 0;

	while (str[i])
	{
		if (str[i] == '/')
			return (2);
		i++;
	}
	return (0);
}

char **completion_split(char *line)
{
	char	**table;
	char	**tmp;
	int		i;

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
		i = 0;
		while(table[i])
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
		// free function (table)
		return (tmp);
	}
	return (table);
	
}

char	*completed_line(char *line, char *str)
{
	int		i;
	char	*left;
	char	*tmp;

	i = ft_strlen(line) - 1;
	while (i >= 0)
	{
		if (line[i] == '/' || line[i] == ' ')
			break;
		i--;
	}
	left = ft_strsub(line, 0, i + 1);
	tmp = ft_strjoin(left, str);
	free(left);
	//free(line);
	return (tmp);
}

void	print_result(char **t, t_line *line)
{
	int	space;
	int i;
	int	total_words;
	int str_max_len;
	int word_per_line;
	int	lines_to_print;
	int	words_to_print;

	total_words = 0;
	str_max_len = 0;
	while (t[total_words])
	{
		if (ft_strlen(t[total_words]) > str_max_len)
		{
			str_max_len = ft_strlen(t[total_words]) + 2;
			total_words++;
		}
		else
			total_words++;
	}
	word_per_line = line->col /str_max_len;
	lines_to_print = total_words/word_per_line;
	words_to_print = (line->nline - 1) * word_per_line;
	i = 0;
	while (total_words)
	{
		ft_putstr(t[i]);
		space = str_max_len - ft_strlen(t[i]);
		while (space)
		{
			ft_putchar(' ');
			space--;
		}
		total_words--;
		words_to_print--;
		if ((words_to_print % word_per_line == 0))
			ft_putchar('\n');
		(i)++;
	}
}

int    auto_completion(t_line *line)
{
	char	**result;
	char	**splited_line;
	int		i;
	int		j;

	splited_line = completion_split(line->str);
	i = 0;
	while (splited_line[i + 1])
		i++;
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
	{
		result = files_dirs_search(splited_line[i], i);
	}
	else
	{
		result = cmd_search(splited_line[0]);
	}
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
