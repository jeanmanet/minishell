/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 10:30:19 by jmanet            #+#    #+#             */
/*   Updated: 2022/11/24 09:32:39 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_files(t_data *data)
{
	data->fd_infile = open(data->infile, O_RDONLY, 0644);
	if (data->fd_infile == -1)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", 2);
		write(2, data->infile, ft_strlen(data->infile));
		write(2, "\n", 1);
	}
	data->fd_outfile = open(data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fd_outfile == -1)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", 2);
		write(2, data->outfile, ft_strlen(data->outfile));
		write(2, "\n", 1);
	}
}

void	close_files(t_data *data)
{
	close (data->fd_infile);
	close (data->fd_outfile);
}
/*
void	close_pipes(t_data *data)
{
	close(data->pipe[0]);
	close(data->pipe[1]);
}
*/
