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

FILE	*ttt;

char	**simplecmd_to_tab(t_simple_cmd *cmd)
{

}

int		env_tab_count(void)
{
	t_variable	*node;
	int			count;
	
	node = g_var.var;
	count = 0;
	while (node)
	{
		if (node->env == 0)
			count++;
		node = node->next;
	}
	return (count);
}

char	**env_to_tab(void)
{
	t_variable	*node;
	char		**argv;
	char		*tmp;
	int			i;
	
	node = g_var.var;
	i = env_tab_count();	
	if (!(argv = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (node)
	{
		if (node->env == 0)
		{
			tmp = ft_strjoin(node->key, "=");
			argv[i] = ft_strjoin(tmp, node->value);
			free(tmp);
			i++;
		}
		node = node->next;
	}
	argv[i] = NULL;
	if (i == 0)
		return (NULL);
	return (argv);
}

int		exec_simple_cmd(t_simple_cmd *cmd)
{

	if (cmd->prefix)
	{
		// get all (io_redirects from: prefix[i]->io_redirect && suffix[i]->io_redirect) and/or (ass_words: prefix->assword)
		// get cmd_path from cmd->word
		// get cmd_args from suffix[i]->word
	}
	else if (cmd->name)
	{
		// get all (io_redirects from: suffix[i]->io_redirect)
		// get cmd_path from cmd->name
		// get cmd_args from suffix[i]->word
	}
	return (0);
}

int		exec_ast(t_pipe_seq *cmd)
{
	int		s_in;
	int		s_out;
	int		s_err;

	s_in = dup(0);
	s_out = dup(1);
	s_err = dup(2);

	// current cmd setup
	exec_simple_cmd(cmd->left);
	// some next cmd setup
	exec_ast(cmd->right);

	return (0);
}

int		execute(t_and_or *cmd, int bg)
{
	ttt = fopen("/dev/ttys004", "w");
	int dp;
	int ret;
	int child;

	// need to fork here
	dp = cmd->dependent;
	while (cmd)
	{
		if (!dp || (dp == 1 && !g_var.exit_status) || (dp == 2 && g_var.exit_status))
		{
			fprintf (ttt, "++++++++++++ andor_cmd [bg:%d]+++++++++++", bg);
			
			ret = exec_ast(cmd->ast);
			g_var.exit_status = ret;
		}
		cmd = cmd->next;
	}
	if (!bg)
	{
		waitpid(child, NULL, 0);
	}
	return (ret);
}

//****************** test ***************************
void	execute_test(t_cmdlist *node)
{
	//*******************
	char *infile;
	char *outfile;
	int  numsimplecommands;
	int  background;

	//**********************
	//save in/out
	int tmpin=dup(0);
	int tmpout=dup(1);

	//set the initial input 
	int fdin;
	if (infile)
	{
		fdin = open(infile,O_RDONLY); 
	}
	else 
	{
		// Use default input
		fdin=dup(tmpin);
	}

	int ret;
	int fdout;
	for(int i=0;i<numsimplecommands; i++)
	{
		//redirect input
		dup2(fdin, 0);
		close(fdin);
		//setup output
		if (i == numsimplecommands - 1)
		{
			// Last simple command 
			if(outfile)
			{
				fdout=open(outfile,O_WRONLY);
			}
			else
			{
			// Use default output
				fdout=dup(tmpout);
			}
		}
		else
		{
			// Not last 
			//simple command
			//create pipe
			int fdpipe[2];
			pipe(fdpipe);
			fdout=fdpipe[1];
			fdin=fdpipe[0];
		}// if/else

		// Redirect output
		dup2(fdout,1);
		close(fdout);

		// Create child process
		ret=fork(); 
		if(ret==0) 
		{
			execvp(scmd[i].args[0], scmd[i].args);
			perror("execvp---->error:");
			_exit(1);
		}
	} //  for

	//restore in/out defaults
	dup2(tmpin,0);
	dup2(tmpout,1);
	close(tmpin);
	close(tmpout);

	if (!background) 
	{
		// Wait for last command
		waitpid(ret, NULL, WUNTRACED | WCONTINUED);
	}
} 

/*
int		runcmd(char *path, char **argv, char **env_tab)
{
	pid_t	child_pid;
	int		child_status;
	pid_t	tpid;

	if (access(path, X_OK) != 0 || verify_type(path) != 2)
	{
		ft_putstr(argv[0]);
		ft_putstr(": Permission denied.\n");
		return (-1);
	}
	child_pid = fork();
	if (child_pid == 0)
	{
		execve(path, argv, env_tab);
		return (0);
	}
	else
	{
		tpid = wait(&child_status);
		while (tpid != child_pid)
		{
			tpid = wait(&child_status);
		}
		return (child_status);
	}
}

char	*valid_cmd_2(char **cmd, char **paths)
{
	int		i;
	char	*path;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd[0]);
		if (access(path, F_OK) == 0)
		{
			free_tab(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

char	*valid_cmd(char **cmd, t_env *head)
{
	char	**paths;

	if (access(cmd[0], F_OK) == 0 && verify_type(cmd[0]) == 2 && ispth(cmd[0]))
		return (ft_strdup(cmd[0]));
	paths = paths_from_env(head);
	if (paths == NULL || verify_type(cmd[0]) == 1 || ispth(cmd[0]))
	{
		free_tab(paths);
		return (NULL);
	}
	return (valid_cmd_2(cmd, paths));
}

int		run_cmd(char **cmd, t_env *head)
{
	char *path;
	char **env_tab;

	path = valid_cmd(cmd, head);
	if (path != NULL)
	{
		env_tab = list_to_tab(head);
		runcmd(path, cmd, env_tab);
		free_tab(env_tab);
		free(path);
		return (0);
	}
	else
	{
		if (!access(cmd[0], F_OK) && verify_type(cmd[0]) != 2 && ispth(cmd[0]))
		{
			ft_putstr(cmd[0]);
			ft_putstr(": Permission denied.\n");
			return (-2);
		}
		ft_putstr("minishell: command not found: ");
		ft_putstr(cmd[0]);
		ft_putstr("\n");
		return (-1);
	}
}
*/