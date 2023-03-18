/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:28:44 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/18 22:41:05 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_command(t_com *command)
{
	int	returnval;
	returnval = 0;
	if (command->args[0] != NULL)
	{
		if (cmd_is_builtin(command))
		{
			returnval = exec_builtin(command);
		}
		else
			returnval = exec_processus(command);
	}
	return (returnval);
}

int	exec_processus(t_com *command)
{
	pid_t	pid;
	char	**cmd;
	char	*relative_cmd;
	int		status;

	cmd = command->args;
	relative_cmd = get_current_command(cmd[0], global_envp);
	if (relative_cmd)
	{
		pid = fork();
		if (pid == 0)
		{
				execve(relative_cmd, cmd, global_envp);
		}
		else
		{
			waitpid(pid, &status, 0);
			free(relative_cmd);
			return (WEXITSTATUS(status));
		}
	}
	return (127);
}
