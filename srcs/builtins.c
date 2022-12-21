/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:47:39 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/21 14:33:42 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(t_com *command)
{
	int		i;

	i = 4;
	while (command->command[i])
	{
		if (ft_isspace(command->command[i]))
			i++;
		if (command->command[i] == '-' && command->command[i + 1] == 'n')
		{
				i += 2;
				//while (ft_isspace(data->command_line[i]))
				//	i++;
				printf("%s", &command->command[i]);
		}
		else
		{
			if (command->command[i] == '-')
				i++;
			//while (ft_isspace(data->command_line[i]))
			//	i++;
			printf("%s\n", &command->command[i]);
		}
	}
	return (0);
}

char	*var_name(char *str)
{
	int	i;
	char	*varname;

	i = 0;
	while (str[i] != '=')
		i++;
	varname = malloc(sizeof(char) * i + 1);
	if (!varname)
		return (NULL);
	i = 0;
	while (str[i] != '=')
	{
		varname[i] = str[i];
		i++;
	}
	varname[i] = '\0';
	return (varname);
}

int	ft_export(t_data *data)
{
	char	**args;
	char	*name;
	char	*value;
	int		returnval;

	args = ft_split(data->command_line, ' ');
	name = var_name(args[1]);
	value = ft_strdup(args[1]);
	returnval = ft_setenv(name, value, 1, data);
	free(name);
	free_tab_str(args);
	return (returnval);
}

int	cmd_is_builtin(t_data *data)
{
	t_com *command;

	command = data->command;
	if (!ft_strncmp(command->command, "exit", 4))
		return (1);
	if (!ft_strncmp(command->command, "cd ", 3))
		return (1);
	if (!ft_strncmp(command->command, "pwd", 3))
		return (1);
	if (!ft_strncmp(command->command, "echo", 4))
		return (1);
	if (!ft_strncmp(command->command, "export", 6))
		return (1);
	return(0);
}

int	exec_builtin(t_data *data)
{
	t_com	*command;

	command = data->command;
	if (!ft_strncmp(command->command, "exit", 4))
	{
		free(command->command);
		exit (0);
	}
	if (!ft_strncmp(command->command, "cd ", 3))
		return (ft_change_directory(data));
	if (!ft_strncmp(command->command, "pwd", 3))
		printf("%s\n", ft_getenv("PWD", data));
	if (!ft_strncmp(command->command, "echo", 4))
		return (ft_echo(command));
	if (!ft_strncmp(command->command, "export", 6))
		return (ft_export(data));
	//faire la builtin "unset"
	return(0);
}
