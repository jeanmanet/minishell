/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:31:12 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/29 09:31:35 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_handler(int sig)
{
		//printf("numero du signal %d\n", sig);
		if (sig == 11)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		if (sig == 2)
			printf("\n");
}
