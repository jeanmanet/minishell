/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 09:17:31 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/19 11:49:50 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char	**ft_import_envp(char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * i + 1);
	if (!new_envp)
		ft_exit_error("Memory allocation error");
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

char	*ft_getenv(char *name, t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], name, ft_strlen(name)))
			return (&data->envp[i][ft_strlen(name) + 1]);
		i++;
	}
	return (NULL);
}

int	ft_addtoenv(char *value, t_data *data)
{
	char	**newenv;
	int		i;

	i = 0;
	while (data->envp[i])
		i++;
	newenv = malloc(sizeof(char *) * i + 1);
	if (!newenv)
		return (0);
	i = 0;
	while (data->envp[i])
	{
		newenv[i] = data->envp[i];
		i++;
	}
	newenv[i] = value;
	i++;
	newenv[i] = NULL;
	free(data->envp);
	data->envp = newenv;
	return (1);
}

int	ft_setenv(char *name, char *value, int overwrite, t_data *data)
{
	int	i;

	i = 0;
	if (ft_ischarset(name, '='))
		return (EINVAL);
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], name, ft_strlen(name)))
		{
			if (overwrite == 1)
			{
				free(data->envp[i]);
				data->envp[i] = value;
				return (0);
			}
		}
		i++;
	}
	if (ft_addtoenv(value, data))
		return (0);
	return (-1);
}
