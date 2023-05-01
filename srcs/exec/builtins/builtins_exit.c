/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:34:48 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/01 17:16:50 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_str_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_com *command, t_data *data)
{
	int	i;
	int	exit_code;

	i = 0;
	if (!command->args[1])
		exit (0);
	exit_code = ft_atoi(command->args[1]);
	if (command->args[2])
	{
		printf("minishell : exit : too many arguments\n");
		return (1);
	}
	else
	{
		if (ft_str_is_numeric(command->args[1]))
		{
			free_mem(data);
			exit (exit_code);
		}
	}
	printf("minishell : exit: %s: numeric argument required\n",
		command->args[i]);
	return (255);
}
