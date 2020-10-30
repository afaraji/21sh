/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 23:36:12 by afaraji           #+#    #+#             */
/*   Updated: 2020/10/29 23:36:21 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "ast.h"

void	print_set_with_typ(void)
{
	t_variable	*node;

	node = g_var.var;
	fprintf(ttt, "\n++++++++++++++++++++++++\n");
	while (node)
	{
		fprintf(ttt, "%d:%s=%s\n", node->env, node->key, node->value);
		node = node->next;
	}
	fprintf(ttt, "++++++++++++++++++++++++\n");

}

//*********** tmp print ************

void	print_io_redirect(t_io_redirect *head)
{
	t_io_redirect *node;

	fprintf(ttt,"IO_redirect: ");
	if (!head)
		return;
	node = head;
	fprintf(ttt,"[type:%s|%d|%s]\n", tokentoa(node->redirect_type), node->io_num, node->filename);
}

void	print_cmdprefix(t_cmd_prefix *head)
{
	t_cmd_prefix *node;

	fprintf(ttt,"------- prefix: ------\n");
	if (!head)
		return;
	node = head;
	if (node->io_redirect)
		print_io_redirect(head->io_redirect);
	if (node->ass_word)
		fprintf(ttt, "assWord [env = %d, %s=%s]\n", node->ass_word->env, node->ass_word->key, node->ass_word->value);
	if (node->prefix)
		print_cmdprefix(node->prefix);
}

void	print_cmdsuffix(t_cmd_suffix *head)
{
	if (!head)
		return;
	fprintf(ttt,"------- suffix: ------\n");
	if (head->io_redirect)
	{
		print_io_redirect(head->io_redirect);
	}
	if (head->word)
	{
		fprintf(ttt, "WORD:[%s]\n", head->word);
	}
	if (head->suffix)
		print_cmdsuffix(head->suffix);

}

void	print_simple_cmd(t_simple_cmd *cmd)
{
	if (!cmd)
		return;
	if (cmd->prefix)
	{
		print_cmdprefix(cmd->prefix);
		fprintf(ttt,"cmdWord ==>[%s]\n", cmd->word);
		print_cmdsuffix(cmd->suffix);
	}
	else if (cmd->name)
	{
		fprintf(ttt,"cmdName ==>[%s]\n", cmd->name);
		print_cmdsuffix(cmd->suffix);
	}
	else
	{
		fprintf(ttt,"naaaaaaaaaaaaaallllll\n");
	}

}

//**********************************
