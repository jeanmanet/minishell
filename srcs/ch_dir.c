/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:52:39 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/28 16:07:50 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_change_directory(t_data *data)
{
	char	pwd[256];

	if (!access(data->args[1], R_OK))
	{
		ft_setenv("OLDPWD", ft_strjoin("OLDPWD=",getcwd(pwd, 256)), 1, data);
		chdir(data->args[1]);
		ft_setenv("PWD", ft_strjoin("PWD=", getcwd(pwd, 256)), 1, data);
		return (0);
	}
	else
	{
		printf("cd: %s: %s\n", strerror(errno), data->args[1]);
		return (1);
	}
}
