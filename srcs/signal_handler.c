/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:31:12 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/21 13:08:00 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sigaction(int signal)
{
	if (signal == SIGINT)//Ctrl + C num 2
	{
		rl_on_new_line();
	}
	if (signal == SIGQUIT)/*Ctrl +\ num 3*/
	{
		// if (data->pid)
		write(1, "Quit: 3\n", 8);
	}
}

void	ft_signal_handler(void)
{
	struct sigaction sigact;

	sigact.sa_handler = ft_sigaction;

	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);




}
