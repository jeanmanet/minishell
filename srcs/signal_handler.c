/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:31:12 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/27 09:12:24 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:31:12 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/14 09:55:45 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(void)
{
	if (g_pid == 0)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		kill(g_pid, SIGINT);
		g_pid = 0;
		printf("\n");
		rl_on_new_line();
	}
}

void	handle_sigquit(void)
{
	if (g_pid == 0)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		kill(g_pid, SIGINT);
		g_pid = 0;
		printf("Quit: 3\n");
		rl_on_new_line();
	}
}

void	ft_sigaction(int signal)
{
	if (signal == SIGINT)
		handle_sigint();
	if (signal == SIGQUIT)
		handle_sigquit();
}

void	ft_signal_handler(void)
{
	struct sigaction	sigact;

	sigact.sa_handler = ft_sigaction;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
}

void	ft_signal_handler_here_doc(int signal)
{
	if (signal == SIGINT)
	{
		//tmp_fd_here_doc = 1;
		// if (fd_here_doc != -1)
		//close(fd_here_doc);
		//printf("handler ctrl c heredoc\n");
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
		// rl_on_new_line();
		// write(0, "\x04", 1);
		//unlink(".here_doc.tmp");
	}
	else if (signal == SIGQUIT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
}

