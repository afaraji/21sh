/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:44:57 by afaraji           #+#    #+#             */
/*   Updated: 2020/10/30 17:45:01 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"

void	free_tab(char **av)
{
	int i;

	i = 0;
	if (!av)
		return ;
	while (av[i])
	{
		ft_strdel(&av[i]);
		i++;
	}
	free(av);
	av = NULL;
}

void			free_list(t_l *head)
{
	t_l	*tmp1;
	t_l	*tmp2;

	tmp1 = head;
	tmp2 = NULL;
	while (tmp1)
	{
		tmp2 = tmp1;
		tmp1 = tmp1->next;
		ft_strdel(&tmp2->data);
		free(tmp2);
	}
}

void	free_l(t_l *list)
{
	if (!list)
		return ;
	free_l(list->next);
	ft_strdel(&(list->data));
	free(list);
	list = NULL;
}

void	free_tokens(t_list_token *tokens)
{
	if (!tokens)
		return ;
	free_tokens(tokens->next);
	tokens->is_ok = 0;
	tokens->type = 0;
	tokens->prec = NULL;
	tokens->next = NULL;
	if (tokens->data)
		ft_strdel(&(tokens->data));
	free(tokens);
	tokens = NULL;
}

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
	free_ast(ast->right);
	free_simple_cmd(ast->left);
	free(ast);
	ast = NULL;
}

void	free_and_or_list(t_and_or *list)
{
	if (!list)
		return ;
	free_and_or_list(list->next);
	free_ast(list->ast);
	free(list);
	list = NULL;
}

void	free_cmd_list(t_cmdlist *list)
{
	if (!list)
		return ;
	free_cmd_list(list->next);
	free_and_or_list(list->and_or);
	free(list);
	list = NULL;
}

void	free_t_var(t_variable *list)
{
	if (!list)
		return ;
	free_t_var(list->next);
	ft_strdel(&(list->key));
	ft_strdel(&(list->value));
	free(list);
	list = NULL;
}

void	free_proc(t_proc *proc)
{
	if (proc->next)
		free_proc(proc->next);
	ft_strdel(&(proc->str));
	free(proc);
	proc = NULL;
}

void	free_aliases(t_alias *alias)
{
	if (alias->next)
		free_aliases(alias->next);
	ft_strdel(&(alias->key));
	ft_strdel(&(alias->sub));
	free(alias);
	alias = NULL;
}

void	free_history_list(t_hist *list)
{
	if (list->next)
		free_history_list(list->next);
	ft_strdel(&(list->hist_str));
	list->next = NULL;
	list->prec = NULL;
	free(list);
	list = NULL;
}

void	free_g_var(void)
{
	free_t_var(g_var.var);
	free_aliases(g_var.aliases);
	free_history_list(g_var.history);
	free_proc(g_var.proc);
}

