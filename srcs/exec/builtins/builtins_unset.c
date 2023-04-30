/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:21:52 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/30 11:32:02 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


int	var_is_in_env(char *varname, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(varname, env[i], ft_strlen(varname)))
			return (1);
		i++;
	}
	return (0);
}

char	**init_newenv(char **oldenv)
{
	int		i;
	char	**newenv;

	i = 0;
	while (oldenv[i])
		i++;
	newenv = malloc(sizeof(char *) * i);
	if (!newenv)
	{
		perror("Memory allocation error");
		exit (0);
	}
	return (newenv);
}

int	ft_unsetenv(char *varname, t_data *data)
{
	int		i;
	int		j;
	char	**newenvp;

	printf("Variable d'env trouvee\n");
	i = 0;
	j = 0;
	newenvp = init_newenv(data->envp);
	while (data->envp[i + j])
	{
		if (ft_strncmp(varname, data->envp[i], ft_strlen(varname)))
			newenvp[i] = data->envp[i + j];
		else
		{
			free(data->envp[i + j]);
			j++;
			newenvp[i] = data->envp[i + j];
		}
		i++;
	}
	newenvp[i] = NULL;
	free(data->envp);
	data->envp = newenvp;
	return (0);
}

int	ft_unset(t_com *command, t_data *data)
{
	int		returnval;
	int		i;

	returnval = 0;
	i = 1;
	while (command->args[i])
	{
		remove_variable(&data->var_list, command->args[i]);
		if (var_is_in_env(command->args[i], data->envp))
			returnval = ft_unsetenv(command->args[i], data);
		i++;
	}
	return (returnval);
}

