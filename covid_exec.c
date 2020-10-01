/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:13:41 by afaraji           #+#    #+#             */
/*   Updated: 2020/02/10 16:14:17 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "run_cmd.c"

int		covid_exec_ast(t_pipe_seq *cmd)
{
    return (0);
}

int main_parse(char *line)
{
	t_list_token    *tokens;
	t_cmdlist		*cmdlist = NULL;
	t_cmdlist		*node;
	int				ret;

	fprintf(ttyfd, "\033[H\033[2J");
    tokens = __tokenize(line);
	// printf("\n");token_print(tokens);printf("\n");
	
	g_var.errno = 0;
	if (lexer(&tokens) || verify_tokens(tokens))
	{
		return (100);
	}
	if (need_append(tokens))
		return (100);
	join_words(tokens);
	cmdlist = token_split_sep_op(tokens);
	// free_tokens(tokens);	
	int i = 0;
	node = cmdlist;
	while (node)
	{
		/*
		execFunc(node);
		// right before exec, this func should impliment what is in lexer.c 
		// (more important) and parser.c (most of it alredy implimented)
		*/

		fprintf(ttyfd, "++++++++++ (cmd: %d | BG: %d) ++++++++++\n", i, node->bg);
		i++;
		print_andor(node);
		ret = execute(node->and_or, node->bg);
		// print_tokenlist(node->and_or->ast);
		fprintf(ttyfd, "-----------------------------------------------------\n");
		node = node->next;
	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	char	*line = NULL;
	int		ret = 0;

	if (init_shell(env))
		return (1);
	line = readline(-1);
	while (1)
	{
		if (ft_strncmp(line, "exit", 4) == 0)
			ft_exit(ft_atoi(&line[4]));
		ret = main_parse(line);
		printf("\n");
		if (line)
			ft_strdel(&line);
		line = readline(0);
		// fprintf(ttyfd, "------------->(%d) - (%s)\n", ret, line);
	}
	(void)ac;
	(void)av;
	return (0);
}