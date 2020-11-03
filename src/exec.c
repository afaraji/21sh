/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaraji <afaraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:13:41 by afaraji           #+#    #+#             */
/*   Updated: 2020/10/31 20:54:52 by afaraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_21sh.h"
#include "../inc/builtins.h"
#include "../inc/parse.h"
#include "../inc/ast.h"
#include "../inc/exec.h"
#include "../inc/ft_free.h"
#include "../inc/readline.h"

int		exec_simple_cmd(t_simple_cmd *cmd)
{
	char		**args;
	char		**env;
	char		*cmd_path;
	t_l			*args_list;
	t_variable	*vars;

	if (!cmd)
		return (404);
	if (do_simple_cmd(cmd))//does prefix and suffix
		return (1);
	args = get_arg_var_sub(cmd);
	if (!args || !args[0])
		exit (0);
	env = env_to_tab(g_var.var, 0);
	if (is_builtin(args[0]))
	{
		//do builtin
		return (builtins(args[0], args, env));
	}
	if (!(cmd_path = get_cmdpath(args[0])))
	{
		return (127);
	}
	ft_set_attr(1);
	execve(cmd_path, args, env);//error handling
	ft_print(STDERR, "shell: permission denied: %s\n", args[0]);
	return (126);
}

int		exec_pipe(t_pipe_seq *cmd)// here !!
{
	int		pfd[2];
	int		status;
	pid_t	pid_l;
	pid_t	pid_r;


	if (cmd->right == NULL)
		exit(exec_simple_cmd(cmd->left));
	if(pipe(pfd) != 0)
		return (1);
	if ((pid_l = fork()) == -1)
		return (2);//should set errno
	if (pid_l == 0)
	{
		close(pfd[0]);
		dup2(pfd[1],STDOUT);
		exit(exec_simple_cmd(cmd->left));
	}
	else
	{
		if ((pid_r = fork()) == -1)
			return (2);//should set errno
		if (pid_r == 0)
		{
			close(pfd[1]);
			dup2(pfd[0],STDIN);
			if (cmd->right->right)
				exec_pipe(cmd->right);
			else
				exit(exec_simple_cmd(cmd->right->left));
		}
		close(pfd[0]);
		close(pfd[1]);
		waitpid(pid_l, NULL, 0);
		waitpid(pid_r, &status, 0);
		// fprintf(ttt,"child_l:[%d] exit(%d)\n", pid_l, tmp);
		// fprintf(ttt,"child_r:[%d] exit(%d)\n", pid_r, status);
		exit(WEXITSTATUS(status));
	}
	return (0);
}

int		exec_ast(t_pipe_seq *cmd, int bg)
{
	int			child;
	int			status;

	if ((status = exec_no_fork(cmd, bg)) != -42)
		return (status << 8);
	status = 0;
	child = fork();
	if (child == 0)
	{
		ft_set_attr(1);
		signal(SIGINT, SIG_DFL);
		// def_io = dup(STDIN);
		exec_pipe(cmd);
	}
	else if (!bg)
	{
		waitpid(child, &status, 0);
		exit_status(status);
		// fprintf(ttt,"P_child:[%d] exit(%d) - (%d)\n", child, WEXITSTATUS(status) , g_var.exit_status);
	}
	else
	{
		// fprintf(ttt, "==++++++not waiting++++++\n");
		add_proc(child);
	}
	return (status);
}

int		execute(t_and_or *cmd, int bg)
{
	int dp;
	int ret = 0;

	while (cmd)
	{
		dp = cmd->dependent;
		if (!dp || (dp == 1 && !g_var.exit_status) || (dp == 2 && g_var.exit_status))
		{
			exit_status(exec_ast(cmd->ast, bg));
			// fprintf(ttt, "===exit stats[%d]===\n", g_var.exit_status);
		}
		cmd = cmd->next;
	}
	return (ret);
}
