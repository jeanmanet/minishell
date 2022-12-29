/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 10:19:13 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/29 10:39:25 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_allocated_mem(t_data *data)
{
	int	i;

	i = 0;
	while (data->args[i])
	{
		free(data->args[i]);
		i++;
	}
	free(data->args);
}


void	ft_free_command(t_data *data)
{
	int	i;

	i = 0;
	while (data->command->args[i])
	{
		free(data->command->args[i]);
		i++;
	}
	free(data->command->args);
	free(data->command->infile);
	free(data->command->outfile);
}
