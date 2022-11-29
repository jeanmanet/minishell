/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:47:39 by jmanet            #+#    #+#             */
/*   Updated: 2022/11/29 12:42:29 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(t_data *data)
{
	int		i;

	i = 4;
	while (data->str[i])
	{
		if (ft_isspace(data->str[i]))
			i++;
		if (data->str[i] == '-' && data->str[i + 1] == 'n')
		{
				i += 2;
				while (ft_isspace(data->str[i]))
					i++;
				printf("%s", &data->str[i]);
				return ;
		}
		else
		{
			if (data->str[i] == '-')
				i++;
			while (ft_isspace(data->str[i]))
				i++;
			printf("%s\n", &data->str[i]);
		}
		return;
	}
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

void	ft_export(t_data *data)
{
	char	**args;
	char	*name;
	char	*value;

	args = ft_split(data->str, ' ');
	name = var_name(args[1]);
	value = ft_strdup(args[1]);
	ft_setenv(name, value, 1, data);
	free(name);
	free_tab_str(args);
}

int	cmd_is_builtin(t_data *data)
{
	if (!ft_strncmp(data->str, "exit", 4))
	{
		free(data->str);
		exit (0);
	}
	if (!ft_strncmp(data->str, "cd ", 3))
	{
		ft_change_directory(data);
		return (1);
	}
	if (!ft_strncmp(data->str, "pwd", 3))
	{
		printf("%s\n", ft_getenv("PWD", data) + 4);
		return (1);
	}
	if (!ft_strncmp(data->str, "echo", 4))
	{
		ft_echo(data);
		return (1);
	}
	if (!ft_strncmp(data->str, "export", 6))
	{
		ft_export(data);
		return (1);
	}
	return(0);
}
