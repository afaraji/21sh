#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

typedef struct      s_lst
{
	char            *s;
	struct s_lst    *next;    
}                   t_lst;

int		is_match(char *pattern, char *s) 
{
	// p = pattern (eg. abc*.???), s = string that we are trying to match to p
	char *p;
	int i = 0,j = 0;
	// this part is to eliminate multiple '*' eg. ls **.c become *.c
	p = (char *)malloc(sizeof(char) * (strlen(pattern) + 1));
	p[0] = pattern[0];
	while (pattern[i])
	{
		if(pattern[i] != '*' || pattern[i - 1] != '*')
			p[j++] = pattern[i];
		i++;
	}
	p[j] = '\0';
	// printf("matching(%s|pattern:%s)\n", s, p);
    // if we reach at the end of both strings it means our strings matches
    if (*p == '\0' && *s == '\0') 
        return (1); 
  
    // if there is still characters in pattern but s is over = fail to match
    if (*p == '*' && *(p+1) != '\0' && *s == '\0') 
        return (0); 
  
    // if the p(pattern) string contains '?', or current characters of both strings match
	// advence to the next char in p and s
    if (*p == '?' || *p == *s) 
        return (is_match(p+1, s+1)); 
  
    // if there is * in p, then there are two possibilities 
    // a) we consider current character of s string 
    // b) we ignore current character of s string. 
    if (*p == '*') 
        return (is_match(p+1, s) || is_match(p, s+1)); 
    return (0); 
}

void	add_to_matched_list(char *str, t_lst **head)
{
	t_lst	*node;
	// printf("matched(%s)\n", str);
	if (!(*head))
	{
		node = (t_lst *)malloc(sizeof(t_lst));
		node->next = NULL;
		node->s = strdup(str);
		*head = node;
	}
	else
	{
		while (node->next)
			node = node->next;
		node->next = (t_lst *)malloc(sizeof(t_lst));
		node->next->next = NULL;
		node->next->s = strdup(str);
	}
}

char	**list_to_tab(t_lst *head)
{
	t_lst	*node;
	int		i = 0;
	char	**tab;

	if (!head)
		return (NULL);
	node = head;
	while(node)
	{
		i++;
		node = node->next;
	}
	tab = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	node = head;
	while (node)
	{
		tab[i] = strdup(node->s);
		node = node->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char    **matching(char *pattern, t_lst *head)
{
	t_lst   *node;
	t_lst   *new_list = NULL;
	char	**matched_tab;

	node = head;
	int i,j;
	i = j = 0;
	while (node)
	{
		if (is_match(pattern, node->s))
			add_to_matched_list(node->s, &new_list);
		node = node->next;
	}
	matched_tab = list_to_tab(new_list);
	// for(int i = 0; matched_tab[i]; i++)
	// 	printf("matched_tab[%d]= %s\n", i, matched_tab[i]);
	return (matched_tab);
}

char    **wild_cards(char *pattern)
{
	DIR *d;
	struct dirent *dir;
	t_lst   *head = NULL;
	t_lst   *node;

	// open current dir to generate a list of strings to match with pattern
	// should be replaced with absolute path depending on input
	d = opendir(".");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			// printf("%s\n", dir->d_name);
			if(head)
			{
				node->next = (t_lst *)malloc(sizeof(t_lst));
				node->next->s = strdup(dir->d_name);
				node = node->next;
				node->next = NULL;
			}
			else
			{
				head = (t_lst *)malloc(sizeof(t_lst));
				head->s = strdup(dir->d_name);
				node = head;
				node->next = NULL;
			}
		}
		closedir(d);
	}
	// pass the pattern and string list to matching func
	return (matching(pattern, head));

}


int main()
{
	char *str = "file*.txt" ; // put here the pattern u r looking for in the current DIR
	char **result;
	int i = 0;
	

	printf("====== %s ====\n", getcwd(NULL, 0));
	result = wild_cards(str);
	while (result[i])
	{
		printf("--> %s\n", result[i++]);
	}

	return 0;
}
