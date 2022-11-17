/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 08:59:42 by jmanet            #+#    #+#             */
/*   Updated: 2022/11/17 18:24:15 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit_error(char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
	exit (errno);
}

void	exit_cmd_strerror(char *cmd_name)
{
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, ": ", 2);
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, "\n", 1);
	exit (0);
}

void	cmd_not_found(char *cmd_name)
{
	write(2, "command not found: ", 19);
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, "\n", 1);
}
