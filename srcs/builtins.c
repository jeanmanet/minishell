/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:47:39 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/29 09:18:14 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(t_com *command)
{
	int		i;

	i = 0;
	if (!command->args[1])
	{
		printf("\n");
		return (0);
	}
	if (!ft_strncmp(command->args[1], "-n", 3))
		i = 2;
	else
		i = 1;
	while (command->args[i])
	{
		printf("%s", command->args[i]);
		i++;
		if (command->args[i])
			printf(" ");
	}
	if (ft_strncmp(command->args[1], "-n", 3))
		printf("\n");
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
	char	*name;
	char	*value;
	int		returnval;
	int		i;

	returnval = 0;
	i = 1;
	while (data->command->args[i])
	{
		name = var_name(data->command->args[i]);
		if (name)
		{
			value = ft_strdup(data->command->args[i]);
			returnval = ft_setenv(name, value, 1, data);
		}
		free(name);
		i++;
	}
	return (returnval);
}

int	cmd_is_builtin(t_data *data)
{
	if (!ft_strncmp(data->command->args[0], "exit", 5))
		return (1);
	if (!ft_strncmp(data->command->args[0], "cd", 3))
		return (1);
	if (!ft_strncmp(data->command->args[0], "pwd", 4))
		return (1);
	if (!ft_strncmp(data->command->args[0], "echo", 5))
		return (1);
	if (!ft_strncmp(data->command->args[0], "export", 7))
		return (1);
	return(0);
}

int	exec_builtin(t_data *data)
{
	if (!ft_strncmp(data->command->args[0], "exit", 5))
	{
		//free(data->command->command);
		exit (0);
	}
	if (!ft_strncmp(data->command->args[0], "cd", 3))
		return (ft_change_directory(data));
	if (!ft_strncmp(data->command->args[0], "pwd", 4))
		printf("%s\n", ft_getenv("PWD", data));
	if (!ft_strncmp(data->command->args[0], "echo", 5))
		return (ft_echo(data->command));
	if (!ft_strncmp(data->command->args[0], "export", 7))
		return (ft_export(data));
	//faire la builtin "unset"
	return(0);
}
