/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:44:57 by afaraji           #+#    #+#             */
/*   Updated: 2020/10/30 17:45:01 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

void	free_suffix(t_cmd_suffix *suff)
{
	if (!suff)
		return ;
	free_suffix(suff->suffix);
	if (suff->io_redirect)
	{
		ft_strdel(&(suff->io_redirect->filename));
		free(suff->io_redirect);
		suff->io_redirect = NULL;
	}
	else if (suff->word)
	{
		ft_strdel(&(suff->word));
	}
	free(suff);
	suff = NULL;
}

void	free_prefix(t_cmd_prefix *pref)
{
	if (!pref)
		return ;
	free_prefix(pref->prefix);
	if (pref->io_redirect)
	{
		ft_strdel(&(pref->io_redirect->filename));
		free(pref->io_redirect);
		pref->io_redirect = NULL;
	}
	else
	{
		ft_strdel(&(pref->ass_word->key));
		ft_strdel(&(pref->ass_word->value));
		free(pref->ass_word);
		pref->ass_word = NULL;
	}
	free(pref);
	pref = NULL;
}

void	free_simple_cmd(t_simple_cmd *cmd)
{
	if (!cmd)
		return ;
	free_prefix(cmd->prefix);
	if (cmd->name)
	{
		ft_strdel(&(cmd->name));
		free_suffix(cmd->suffix);
	}
	else if (cmd->word)
	{
		ft_strdel(&(cmd->word));
		free_suffix(cmd->suffix);
	}
	cmd->name = NULL;
	cmd->word = NULL;
	free(cmd);
	cmd = NULL;
}

void	free_ast(t_pipe_seq *ast)
{
	if (!ast)
		return ;
	if (ast->right)
		free_ast(ast->right);
	free_simple_cmd(ast->left);
	free(ast);
	ast = NULL;
}

void	free_and_or_list(t_and_or *list)
{
	if (!list)
		return ;
	if (list->next)
		free_and_or_list(list->next);
	free_ast(list->ast);
	free(list);
	list = NULL;
}
