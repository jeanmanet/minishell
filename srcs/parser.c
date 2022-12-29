/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:55:24 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/29 11:03:00 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_get_nbcmds(char **str)
{
	int	i;
	int	nbcmds;

	i = 0;
	nbcmds = 0;
	if (str[i])
		nbcmds++;
	while (str[i])
	{
		if (!ft_strncmp(str[i], "|", 2))
			nbcmds++;
		i++;
	}
	return (nbcmds);
}

int	parse_commandline(t_data *data)
{
	int		returnval;
	int		nb_cmds;
	int		i;

	i = 1;
	returnval = 0;
	ft_command_line_to_args(data);
//	ft_print_args(data->args);
	ft_parse_args(data);
//	ft_print_args(data->args);
	nb_cmds = ft_get_nbcmds(data->args);
	while (i <= nb_cmds)
	{
		ft_make_command(i, data);
		returnval =	exec_command(data);
		ft_free_command(data);
		i++;
	}
	ft_free_allocated_mem(data);
	return (returnval);
}



