/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ch_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:52:39 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/07 14:04:01 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_change_directory(t_data *data)
{
    char pwd[256];
    struct stat sb;

    if (data->command->args[1] == NULL)
        return (0);
    if (stat(data->command->args[1], &sb) == 0)
	{
        if (S_ISDIR(sb.st_mode))
        {
            ft_setenv("OLDPWD", ft_strjoin("OLDPWD=",getcwd(pwd, 256)), 1, data);
            chdir(data->command->args[1]);
            ft_setenv("PWD", ft_strjoin("PWD=", getcwd(pwd, 256)), 1, data);
            return (0);
        }
        else
        {
            printf("cd: %s: Not a directory\n", data->command->args[1]);
            return (1);
        }
    } else
	{
        printf("cd: %s: %s\n", data->command->args[1], strerror(errno));
        return (1);
    }
}
