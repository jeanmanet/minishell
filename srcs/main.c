/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:03:37 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/29 10:44:00 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(*data));
	data->command = malloc(sizeof(data->command));
	data->envp = ft_import_envp(envp, data);
	if (argc > 1)
		ft_exec_scriptfile(argv);
	while (1)
	{
		//signal(SIGSEGV, ft_signal_handler);
		//signal(SIGINT, ft_signal_handler);
		//signal(SIGQUIT, ft_signal_handler);
		data->command_line = readline("minishell > ");
		add_history(data->command_line);
		data->endstatus = parse_commandline(data);
		printf("valeur de sortie du programme : %d\n", data->endstatus);
	}
	return (0);
}
