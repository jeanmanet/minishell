/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:00:26 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/20 09:00:48 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_redirect_input(t_data *data)
{
	int	fd;

	fd = open(data->command->infile, O_RDONLY, 0644);
	if (fd == -1)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", 2);
		write(2, data->command->infile, ft_strlen(data->command->infile));
		write(2, "\n", 1);
		return (-1);
	}
	else
		dup2(fd, 0);
	close(fd);
	return (0);
}


int	ft_redirect_output(t_data *data)
{
	int	fd;

	fd = open(data->command->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd  == -1)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", 2);
		write(2, data->command->outfile, ft_strlen(data->command->outfile));
		write(2, "\n", 1);
		return (-1);
	}
	else
		dup2(fd, 1);
	close(fd);
	return (0);
}

int	ft_redirect_io (t_com *command, t_data *data)
{
	int	returnval;

	returnval = 0;
	(void)command;
	(void)data;
	//fonction appelee a l'execution, qui appelle
	//ft_redirect_input et/ou ft_redirect_output si necessaire

	return(returnval);
}
