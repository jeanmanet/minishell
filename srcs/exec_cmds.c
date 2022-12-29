/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:28:44 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/29 09:29:43 by jmanet           ###   ########.fr       */
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
			ft_redirect_io(data);
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
	int		status;

	cmd = data->command->args;
	cmd[0] = get_current_command(cmd[0], data->envp);
	if (cmd[0])
	{
		pid = fork();
		if (pid == 0)
		{
			if (!ft_redirect_io(data))
				execve(cmd[0], cmd, data->envp);
			else
				exit(1);
		}
		else
		{
			waitpid(pid, &status, 0);
			return (WEXITSTATUS(status));
		}
	}
	return (127);
}
