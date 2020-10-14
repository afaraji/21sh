#include "readline.h"
#include "parse.h"

void	print_tab(char **tabl)
{
	int		i;

	i = 0;
	while (tabl[i])
	{
		fprintf(ttyfd, "%s\n", tabl[i]);
		if (i == 20)
			break;
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
		printf("%d : %s\n", i , node->data);
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
	if (i == -1)
		return (ft_strdup("."));
	else
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
			var_list = names_list(var->key, var_list);
		var = var->next;
	}
	var_tab = tab_from_list(var_list);
	ft_free_list(var_list);
	return(var_tab);
}

char	**files_dirs_search(char *str)
{
	DIR     *d;
	struct  dirent *dir;
	char    *to_cmp;
	char    *path;
	t_simple_lst   *files_dirs_list;
	char    **dir_tab;

	path = get_path(str);
	to_cmp = get_to_cmp(str);
	files_dirs_list = NULL;
	d = opendir(path);
	if (d)
	{
		while ((dir = readdir(d)))
		{
			if (!ft_strcmp("", to_cmp) || !ft_strncmp(dir->d_name, to_cmp, ft_strlen(to_cmp)))
			{
				if (ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, ".."))
					files_dirs_list = names_list(dir->d_name, files_dirs_list);
			}
		}
	}
	closedir(d);
	dir_tab = tab_from_list(sort_list(files_dirs_list));
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
	char *builtins_list[] = {"cd", "echo", "export", "alias", "unalias",
						"exit", "type", "fc", "set", "unset", NULL};

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
	cmd_tab = tab_from_list((cmd_list));
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
	free(line);
	return (tmp);
}

void	print_result(char **t)
{
	int i;
	int mod;
	int test;
	int	space;
	int nlines;
	int column;
	int	total_words;
	int str_max_len;
	int word_per_line;
	int	lines_to_print;
	int	words_to_print;

	column = tgetnum("co");
	nlines = tgetnum("li");
	total_words = 0;
	while (t[total_words])
	{
		if (total_words - 1 > 0 && (ft_strlen(t[total_words]) >= ft_strlen(t[total_words - 1])))
			str_max_len = ft_strlen(t[total_words]) + 2;
		total_words++;
	}
	word_per_line = column/str_max_len;
	lines_to_print = total_words/word_per_line;
	words_to_print = nlines * word_per_line;
	//fprintf(ttyfd, "column : %d, nlines : %d, total_words : %d, word_per_line : %d\n",column,  nlines, total_words, word_per_line);
	fprintf(ttyfd, "lines_to_print : %d, words_to_print : %d\n", lines_to_print, words_to_print);
	if (lines_to_print < nlines)
	{
		i = 0;
		while (words_to_print && t[i])
		{
			if (total_words % column == column - 1)
				ft_putchar('\n');
			ft_putstr(t[i]);
			words_to_print--;
			i++;
		}
	}
	else
	{
		i = 0;
		while (words_to_print && t[i])
		{
			fprintf(ttyfd, "words_to_print : %d\n", words_to_print);
			ft_putstr(t[i]);
			space = str_max_len - ft_strlen(t[i]);
			fprintf(ttyfd, "str_max_len : %d, ft_strlen(t[i]) : %zu,space : %d\n", str_max_len, ft_strlen(t[i]) ,space);
			// while (space)
			// {
			// 	fprintf(ttyfd, "space : %d\n", space);
			// 	ft_putchar(' ');
			// 	space--;
			// }
			words_to_print--;
			if ((words_to_print%word_per_line == 0))
				ft_putchar('\n');
			i++;
		}
	}
	// max ft_strlen(t[i]) ==> + 2 space
	// word / ligne
	/* nombre de ligne a affiche |
	   should know available ligne in terminal*/
	// split tab to the available lines
}

void    auto_completion(t_line *line)
{
	char **result;
	char **splited_line;
	int i;
	int j;

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
	else if (i != 0 || is_path(splited_line[i]) != 0)
	{
		result = files_dirs_search(splited_line[i]);
	}
	else
	{
		result = cmd_search(splited_line[0]);
	}
	j = 0;
	while (result[j + 1])
		j++;
	if (j == 0)
	{
		line->str = completed_line(line->str, result[0]);
		display_line(line);
		move_curs_right(line);
	}
	else
	{
		tputs(tgetstr("sc", NULL), 1, ft_intputchar);
		ft_putchar('\n');
	//	print_tab(result);
		print_result(result);
		//display_line(line);
		tputs(tgetstr("rc", NULL), 1, ft_intputchar);
	}
}
