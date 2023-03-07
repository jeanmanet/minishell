/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:28:44 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/07 12:34:09 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_command(t_data *data)
{
	int	returnval;
	returnval = 0;
	if (data->command->args[0] != NULL)
	{
		if (cmd_is_builtin(data))
		{
			returnval = exec_builtin(data);
			dup2(0,1);
		}
		else
			returnval = exec_processus(data);
	}
	return (returnval);
}

int	exec_processus(t_data *data)
{
	pid_t	pid;
	char	**cmd;
	char	*relative_cmd;
	int		status;

	cmd = data->command->args;
	relative_cmd = get_current_command(cmd[0], data->envp);
	if (relative_cmd)
	{
		pid = fork();
		if (pid == 0)
		{
				execve(relative_cmd, cmd, data->envp);
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
