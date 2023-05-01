/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:21:04 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/01 16:18:45 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	export_local_var_to_env(char *varname, t_data *data)
{
	t_lst_var	*var_list;
	char		*temp;
	char		*export_value;

	export_value = ft_strjoin(varname, "=");
	var_list = data->var_list;
	while (var_list)
	{
		if (!ft_strncmp(varname, var_list->name, ft_strlen(varname)))
		{
			temp = export_value;
			export_value = ft_strjoin(export_value, var_list->value);
			free(temp);
			return (ft_setenv(varname, export_value, 1, data));
		}
		var_list = var_list->next;
	}
	return (0);
}

int	export_assignment(char *varname, char *assignment, t_data *data)
{
	int	returnval;

	returnval = (ft_setenv(varname, ft_strdup(assignment), 1, data));
	free(varname);
	return (returnval);
}

int	ft_export(t_com *command, t_data *data)
{
	char	*name;
	int		returnval;
	int		i;

	returnval = 0;
	i = 1;
	while (command->args[i])
	{
		if (var_exist_in_locallist(command->args[i], data->var_list))
			returnval = export_local_var_to_env(command->args[i], data);
		else
		{
			name = get_var_name_in_assignment(command->args[i]);
			if (name)
				export_assignment(name, command->args[i], data);
			else
				printf("export : `%s': not a valid identifier\n",
					command->args[i]);
		}
		i++;
	}
	return (returnval);
}
