/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:47:39 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/21 20:37:06 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(t_com *command)
{
	int		i;
	char	**strs;

	strs = ft_split(command->command, ' ');
	if (strs[1])
	{
		if (!ft_strncmp(strs[1], "-n", 2))
			i = 2;
		else
			i = 1;
		while (strs[i])
		{
			printf("%s", strs[i]);
			i++;
			if (strs[i])
				printf(" ");
		}
		if (ft_strncmp(strs[1], "-n", 2))
			printf("\n");
	}
	free_tab_str(strs);
	return (0);
}

char	*var_name(char *str)
{
	int	i;
	char	*varname;

	i = 0;
	if (!ft_ischarset(str, '='))
		return (NULL);
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

	returnval = 0;
	args = ft_split(data->command_line, ' ');
	if (args[1])
	{
		name = var_name(args[1]);
		if (name)
		{
			value = ft_strdup(args[1]);
			returnval = ft_setenv(name, value, 1, data);
		}
		free(name);
	}
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
