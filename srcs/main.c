/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:03:37 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/10 09:23:29 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Attention, mettre des doubles guillemets vides pour une commande vide
// laissent ouverts de nouveaux processus qui retournent au prompt
// puisque la commande est null et non executée... A fixer !!!

int	check_quotes(char *str)
{
	int		i;
	int		nb_quotes;
	char	c;

	i = 0;
	nb_quotes = 0;
	while (str[i])
	{
		if ((ft_lexing(str[i]) == LEX_SQUOTE)
			|| (ft_lexing(str[i]) == LEX_DQUOTE))
		{
			c = str[i++];
			nb_quotes++;
			while (str[i] && str[i] != c)
				i++;
			if (str[i] == c)
				nb_quotes++;
		}
		i++;
	}
	if (nb_quotes % 2 != 0)
		printf("Error in command, some quotes aren't closed \n");
	return (!(nb_quotes % 2));
}

void	prompt(t_data *data)
{
	//signal(SIGSEGV, ft_signal_handler);
	//signal(SIGINT, ft_signal_handler);
	//signal(SIGQUIT, ft_signal_handler);
	data->command_line = readline("minishell > ");
	add_history(data->command_line);
	if (check_quotes(data->command_line))
	{
		data->token_list = parse_commandline(data->command_line);
		printf("Tokens dans la liste : \n");
		print_tokens(data->token_list);
		build_command(data);
		data->endstatus = exec_command(data);
		free_mem(data);
	}
	else
		free(data->command_line);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	data = malloc(sizeof(*data));
	data->command = malloc(sizeof(data->command));
	data->envp = ft_import_envp(envp, data);
	if (argc > 1)
	{
		printf("Invalid Arguments ");
		printf("this minishell doesn't execute scriptfiles !\n");
	}
	while (1)
	{
		prompt(data);
	}
	return (0);
}
