/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:52:39 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/20 13:31:31 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_change_directory(t_data *data)
{
	char	pwd[256];
	char	**cmd;

	cmd = ft_split(data->command_line, ' ');

	if (!access(cmd[1], R_OK))
	{
		ft_setenv("OLDPWD", ft_strjoin("OLDPWD=",getcwd(pwd, 256)), 1, data);
		chdir(cmd[1]);
		ft_setenv("PWD", ft_strjoin("PWD=", getcwd(pwd, 256)), 1, data);
		free_tab_str(cmd);
		return (0);
	}
	else
	{
		printf("cd: %s: %s\n", strerror(errno), cmd[1]);
		free_tab_str(cmd);
		return (1);
	}
}
