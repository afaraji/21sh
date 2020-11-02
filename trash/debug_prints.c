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

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

FILE *ttt;
FILE *ttyfd;

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


void	token_print(t_list_token *node)
{
	fprintf(ttt, "\n");
	while (node)
	{
		if(node->type == WORD)
			fprintf(ttt, "[%s:%d]", node->data, node->type);
		else if(node->type == QUOTE || node->type == DQUOTE)
			fprintf(ttt, "{%d:%s}", node->is_ok, node->data);
		else
		{
			//fprintf(ttt, "(%d)", node->type);
			switch (node->type)
			{
			case -1:
				fprintf(ttt, "_");
				break;
			case -4:
				fprintf(ttt, ";");
				break;
			case -5:
				fprintf(ttt, "(&&)");
				break;
			case -6:
				fprintf(ttt, "||");
				break;
			case -10:
				fprintf(ttt, "|");
				break;
			case -11:
				fprintf(ttt, "&");
				break;
			case -12:
				fprintf(ttt, "[%s:%d]", node->data, node->type);
				break;
			case -20:
				fprintf(ttt, ">");
				break;
			case -21:
				fprintf(ttt, ">>");
				break;
			case -22:
				fprintf(ttt, "<");
				break;
			case -30:
				fprintf(ttt, "<<");
				break;

			default:
				fprintf(ttt, "[%d]", node->type);
				break;
			}
		}
		node = node->next;
	}
	fprintf(ttt, "\n");
}

void	token_print_inverse(t_list_token *node)
{
	fprintf(ttt, "\n");
	while (node->next)
		node = node->next;

	while (node)
	{
		if(node->type == WORD)
			fprintf(ttt, "[%s]", node->data);
		else if(node->type == QUOTE || node->type == DQUOTE)
			fprintf(ttt, "{%d:%s}", node->is_ok, node->data);
		else
		{
			//fprintf(ttt, "(%d)", node->type);
			switch (node->type)
			{
			case -1:
				fprintf(ttt, "_");
				break;
			case -4:
				fprintf(ttt, ";");
				break;
			case -5:
				fprintf(ttt, "(&&)");
				break;
			case -6:
				fprintf(ttt, "||");
				break;
			case -10:
				fprintf(ttt, "|");
				break;
			case -11:
				fprintf(ttt, "&");
				break;
			case -12:
				fprintf(ttt, "[%s]", node->data);
				break;
			case -20:
				fprintf(ttt, ">");
				break;
			case -21:
				fprintf(ttt, ">>");
				break;
			case -22:
				fprintf(ttt, "<");
				break;
			case -30:
				fprintf(ttt, "<<");
				break;

			default:
				fprintf(ttt, "[%d]", node->type);
				break;
			}
		}
		node = node->prec;
	}
	fprintf(ttt, "\n");
}

//*************************************************

void	print_tokenlist(t_pipe_seq *ast)
{
	t_simple_cmd	*node;

	if (!ast)
		return;
	node = ast->left;
	print_simple_cmd(node);
	print_tokenlist(ast->right);
}

void	print_andor(t_cmdlist *list)
{
	t_and_or	*node;

	node = list->and_or;
	while (node)
	{
		fprintf(ttt,"+-+-+-+-+-+-+-+-+-+-+---+-+\ndependent ===>[%d]\n", node->dependent);
		print_tokenlist(node->ast);
		node = node->next;
	}

}
