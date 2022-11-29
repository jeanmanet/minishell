/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:52:39 by jmanet            #+#    #+#             */
/*   Updated: 2022/11/29 11:11:18 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_change_directory(t_data *data)
{
	char	pwd[200];
	char	**cmd;

	cmd = ft_split(data->str, ' ');

	if (!access(cmd[1], R_OK))
	{
		ft_setenv("OLDPWD", ft_strjoin("OLDPWD=",getcwd(pwd, 200)), 1, data);
		chdir(cmd[1]);
		ft_setenv("PWD", ft_strjoin("PWD=", getcwd(pwd, 200)), 1, data);
	}
	else
		printf("cd: %s: %s\n", strerror(errno), cmd[1]);
	free_tab_str(cmd);
	return (0);
}
