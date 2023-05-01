/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:03:37 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/01 19:35:30 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	g_pid;

int	check_quotes(char *str)
{
	int		i;
	int		nb_quotes;
	char	c;

	i = 0;
	nb_quotes = 0;
	if (!str || !*str)
		return (0);
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
	ft_signal_handler();
	data->command_line = readline("minishell > ");
	add_history(data->command_line);
	if (data->command_line)
	{
		if (ft_strlen(data->command_line) > 0
			&& check_quotes(data->command_line))
		{
			data->token_list = tokenizer(data->command_line);
			expand_vars_in_tokenlist(data);
			ft_add_var(data);
			parse_token_list(data);
			data->endstatus = execute_ast(data);
			data->endvar = ft_itoa(data->endstatus);
			edit_variable(&data->var_list, "?", data->endvar);
			free_mem(data);
		}
		else
			free(data->command_line);
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}

void	init_local_var_list(t_data *data, char **envp)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	add_variable(&data->var_list, "?", "0");
	while (envp[i])
	{
		var = get_var_name_in_assignment(envp[i]);
		value = get_var_value_in_assignment(envp[i]);
		add_variable(&data->var_list, var, value);
		free(var);
		free(value);
		i++;
	}
}

t_data	*data_init(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(*data));
	if (!data)
		ft_exit_error("Memory allocation error \n");
	data->commands_tree = malloc(sizeof(t_ast));
	if (!data->commands_tree)
		ft_exit_error("Memory allocation error \n");
	data->commands_tree->root = NULL;
	data->envp = ft_import_envp(envp);
	data->var_list = NULL;
	data->pid = 0;
	init_local_var_list(data, envp);
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	data = data_init(envp);
	if (argc > 1)
	{
		printf("Invalid argument(s), ");
		printf("this minishell doesn't execute scriptfiles !\n");
	}
	else
		while (1)
			prompt(data);
	return (0);
}
