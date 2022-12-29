/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:49:32 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/29 10:48:38 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_command(t_data *data)
{
	data->command->infile = malloc(sizeof(char*));
	ft_bzero(data->command->infile, sizeof(char*));
	data->command->outfile = malloc(sizeof(char*));
	ft_bzero(data->command->outfile, sizeof(char*));
	data->command->args = malloc(sizeof(char*) * (data->nbargs + 1));
	if (!data->command->args)
		ft_exit_error("Memory Allocation Error\n");
	//data->command->fd_input = 1;
	//data->command->fd_output = 1;
}

// Fonction a diviser en plusieurs sous fontions (ex ft_get_args, ft_get_input, ft_get_output...)
void	ft_make_command(int cmd_number, t_data *data)
{

	ft_init_command(data);
	(void)cmd_number;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->args[i])
	{
		if (data->args[i][0] == '<')
		{
			free(data->command->infile);
			data->command->infile = ft_strdup(data->args[i + 1]);
			i += 2;
		}
		else if (data->args[i][0] == '>')
		{
			free(data->command->outfile);
			data->command->outfile = ft_strdup(data->args[i + 1]);
			i += 2;
		}
		else if (!ft_strncmp(data->args[i], "|", 2))
		{
			break;
		}
		else
		{
			data->command->args[j] = ft_strdup(data->args[i]);
			j++;
			i++;
		}
	}
	data->command->args[j] = NULL;
}
