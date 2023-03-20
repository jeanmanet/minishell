/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:28:44 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/20 16:47:01 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_command(t_com *command, t_data *data)
{
	int	returnval;
	int saved_stdin;
	int saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	returnval = 0;
	if (!ft_redirect_io(command) && command->args[0] != NULL)
	{
		if (cmd_is_builtin(command))
			returnval = exec_builtin(command, data);
		else
			returnval = exec_processus(command, data);
	}
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	if (command->cmd_input_mode == CMD_HERE_DOC)
	{
		unlink(command->infile);
		free(command->infile);
	}
	return (returnval);
}

int	exec_processus(t_com *command, t_data *data)
{
	pid_t	pid;
	char	**cmd;
	char	*absolute_cmd;
	int		status;

	cmd = command->args;
	absolute_cmd = get_absolute_command(cmd[0], data->envp);
	if (absolute_cmd)
	{
		pid = fork();
		if (pid == 0)
			execve(absolute_cmd, cmd, data->envp);
		else
		{
			waitpid(pid, &status, 0);
			free(absolute_cmd);
			return (WEXITSTATUS(status));
		}
	}
	return (127);
}
