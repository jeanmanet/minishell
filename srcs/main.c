/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:03:37 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/07 14:01:14 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/* A faire :

- Ajouter SQUOTE ET DQUOTE dans le parser

*/

void	prompt(t_data *data)
{

	//signal(SIGSEGV, ft_signal_handler);
	//signal(SIGINT, ft_signal_handler);
	//signal(SIGQUIT, ft_signal_handler);
	data->command_line = readline("minishell > ");
	add_history(data->command_line);
	data->token_list = parse_commandline(data->command_line);
	printf("Tokens dans la liste : ");
	print_tokens(data->token_list);
	build_command(data);
	data->endstatus = exec_command(data);
	free_mem(data);
	//data->endstatus = parse_commandline(data);
	// printf("valeur de sortie du programme : %d\n", data->endstatus);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	data = malloc(sizeof(*data));
	data->command = malloc(sizeof(data->command));
	data->envp = ft_import_envp(envp, data);
	if (argc > 1)
		printf("Invalid Arguments, this minishell doesn't execute scriptfiles !\n");
	while (1)
	{
		prompt(data);
	}
	return (0);
}
