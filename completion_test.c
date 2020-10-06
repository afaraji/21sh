#include "readline.h"

typedef struct s_lst
{
    char *name;
    struct s_lst *next;
}               t_lst;

char    *get_path(char *str)
{

}

char    **dir_search(char *str)
{
    DIR *d;
    struct dirent *dir;
    char    *path;
    t_lst  *dir_list;
    char    **dir_tab;

    path = get_path(str);
    d = opendir(path);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (ft_strcmp(path, dir->d_name))
                return(dir->d_name);
            //printf("%s\n", dir->d_name);
        }
        closedir(d);
}

int is_path(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == "/")
            return (2);
        i++;
    }
    return (0);
}

char **completion_split(char *line)
{
    return (ft_strsplit(line, " "));
}

void    auto_completion(char *line)
{
    char **result;
    char **splited_line;
    int i;

    splited_line = completion_split(line);
    i = 0;
    while (splited_line[i + 1])
        i++;
    if (i != 0 || is_path(splited_line[i]) != 0)
        result = dir_search(splited_line[i]);
    else
        result = cmd_search(splited_line[0]);
    i = 0;
    while (result[i + 1])
        i++;
    if (i == 0)
    {
        free(*line);
        *line = ft_strdup(result[0]);
        display();
    }
    else
    {
        ft_putchar("\n");
        printf(result);
        display()
    }
    

}










int main()
{   
    auto_completion("ls");
    return 0;
}