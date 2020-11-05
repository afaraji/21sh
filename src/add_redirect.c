/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:30:04 by afaraji           #+#    #+#             */
/*   Updated: 2020/11/03 17:30:11 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

char			*io_file(t_list_token **cmd, t_list_token **end, int *r_type)
{
	char	*file;

	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	if ((*cmd)->type >= GRTAND && (*cmd)->type <= GRT)
	{
		*r_type = (*cmd)->type;
		*cmd = (*cmd)->next;
		while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
			*cmd = (*cmd)->next;
		if (*cmd && ((*cmd)->type == WORD || (*cmd)->type == QUOTE || (*cmd)->type == DQUOTE))
		{
			if (is_valid_file((*cmd)->data, (*cmd)->next))
			{
				file = ft_strdup((*cmd)->data);
				if (*r_type == SMLAND && !is_all_digits(file) && ft_strcmp(file, "-"))
				{
					g_var.errno = 125;
					*cmd = NULL;
					ft_putstr_fd("expected file number, found: ", 2);
					ft_putstr_fd(file, 2);
					ft_putchar_fd('\n', 2);
					return (NULL);
				}
				*cmd = (*cmd)->next;
				return (file);
			}
			return ("");
		}
		ft_putstr_fd("syntax error, unexpected token near -- '", 2);
		if (*cmd)
		{
			ft_putstr_fd(tokentoa((*cmd)->type), 2);
		}
		else
		{
			ft_putstr_fd(tokentoa((*end)->type), 2);
		}
		ft_putstr_fd("'\n", 2);
		g_var.errno = 120;
		*cmd = NULL;
		return (NULL);
	}
	return (NULL);
}

char			*io_here(t_list_token **cmd, t_list_token **end, int *r_type)
{
	char	*file;

	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	if ((*cmd)->type == SMLSML)
	{
		*r_type = (*cmd)->type;
		*cmd = (*cmd)->next;
		while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
			*cmd = (*cmd)->next;
		if (*cmd && ((*cmd)->type == WORD || (*cmd)->type == QUOTE || (*cmd)->type == DQUOTE))
		{
			if (is_valid_file((*cmd)->data, (*cmd)->next))
			{
				file = ft_strdup((*cmd)->data);
				*cmd = (*cmd)->next;
				return (file);
			}
			return ("");
		}
		ft_putstr_fd("syntax error, unexpected token near '", 2);
		if (*cmd)
		{
			ft_putstr_fd(tokentoa((*cmd)->type), 2);
		}
		else
		{
			ft_putstr_fd(tokentoa((*end)->type), 2);
		}
		ft_putstr_fd("'\n", 2);
		g_var.errno = 121;
		*cmd = NULL;
		return (NULL);
	}
	return (NULL);
}

t_io_redirect	*io_redirect(t_list_token **cmd, t_list_token **end)
{
	t_io_redirect	*io_r;
	t_list_token	*node;

	while (*cmd && (*cmd)->type == SPACE && *cmd != *end)
		*cmd = (*cmd)->next;
	if (!cmd || !(*cmd) || g_var.errno)
		return (NULL);
	io_r = (t_io_redirect *)malloc(sizeof(t_io_redirect));
	io_r->io_num = -1;
	io_r->filename = io_file(cmd, end, &(io_r->redirect_type));
	if (io_r->filename)
	{
		return (io_r);
	}
	io_r->filename = io_here(cmd, end, &(io_r->redirect_type));
	if (io_r->filename)
	{
		return (io_r);
	}
	if (*cmd && (*cmd)->type == WORD && (*cmd)->next)
	{
		if (is_all_digits((*cmd)->data) && (*cmd)->next->type != SPACE)
		{
			node = *cmd;
			io_r->io_num = ft_atoi((*cmd)->data);
			*cmd = (*cmd)->next;
			if (!(*cmd))
			{
				*cmd = node;
				free(io_r);
				return (NULL);
			}
			io_r->filename = io_file(cmd, end, &(io_r->redirect_type));
			if (io_r->filename)
			{
				return (io_r);
			}
			io_r->filename = io_here(cmd, end, &(io_r->redirect_type));
			if (io_r->filename)
			{
				return (io_r);
			}
			if (g_var.errno)
			{
				free(io_r);
				return (NULL);
			}
			*cmd = node;
		}
	}
	free(io_r);
	return (NULL);
}
