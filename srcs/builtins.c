/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:47:39 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/20 13:53:12 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(t_data *data)
{
	int		i;

	i = 4;
	while (data->command_line[i])
	{
		if (ft_isspace(data->command_line[i]))
			i++;
		if (data->command_line[i] == '-' && data->command_line[i + 1] == 'n')
		{
				i += 2;
				while (ft_isspace(data->command_line[i]))
					i++;
				printf("%s", &data->command_line[i]);
		}
		else
		{
			if (data->command_line[i] == '-')
				i++;
			while (ft_isspace(data->command_line[i]))
				i++;
			printf("%s\n", &data->command_line[i]);
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
	if (!ft_strncmp(data->command_line, "exit", 4))
		return (1);
	if (!ft_strncmp(data->command_line, "cd ", 3))
		return (1);
	if (!ft_strncmp(data->command_line, "pwd", 3))
		return (1);
	if (!ft_strncmp(data->command_line, "echo", 4))
		return (1);
	if (!ft_strncmp(data->command_line, "export", 6))
		return (1);
	return(0);
}

int	exec_builtin(t_data *data)
{
	if (!ft_strncmp(data->command_line, "exit", 4))
	{
		free(data->command_line);
		exit (0);
	}
	if (!ft_strncmp(data->command_line, "cd ", 3))
		return (ft_change_directory(data));
	if (!ft_strncmp(data->command_line, "pwd", 3))
		printf("%s\n", ft_getenv("PWD", data));
	if (!ft_strncmp(data->command_line, "echo", 4))
		return (ft_echo(data));
	if (!ft_strncmp(data->command_line, "export", 6))
		return (ft_export(data));
	//faire la builtin "unset"
	return(0);
}
