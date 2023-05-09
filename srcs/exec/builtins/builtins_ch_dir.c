/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ch_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:52:39 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/09 14:39:50 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_change_directory(t_com *command, t_data *data)
{
	char		pwd[256];
	struct stat	sb;

	if (command->args[1] == NULL)
		return (0);
	if (stat(command->args[1], &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode))
		{
			edit_variable(&data->var_list, "OLDPWD", getcwd(pwd, 256));
			export_local_var_to_env("OLDPWD", data);
			chdir(command->args[1]);
			edit_variable(&data->var_list, "PWD", getcwd(pwd, 256));
			export_local_var_to_env("PWD", data);
			return (0);
		}
		else
		{
			printf("cd: %s: Not a directory\n", command->args[1]);
			return (1);
		}
	}
	else
		printf("cd: %s: %s\n", command->args[1], strerror(errno));
	return (1);
}
