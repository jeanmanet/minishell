/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:55:24 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/21 15:41:22 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_com	*ft_command_init()
{
	t_com	*command;

	command = malloc(sizeof(command));
	command->command = malloc(1);
	if (!command->command)
		ft_exit_error("Memory Allocation Error\n");
	command->command[0] = '\0';
	command->infile = NULL;
	command->outfile = NULL;
	command->infile_mod = 0;
	command->outfile_mod = 0;
	command->input = stdin;
	command->output = stdout;

	return (command);
}

int ft_change_input(char* substr, t_com *command)
{
	(void)substr;
	(void)command;
	return (0);
}

int ft_change_output(char* substr, t_com *command)
{
	(void)substr;
	(void)command;
	return (0);
}

int ft_get_double_quote_arg(char* substr, t_com *command)
{
	(void)substr;
	(void)command;
	return (0);
}

int ft_get_quote_arg(char* substr, t_com *command)
{
	(void)substr;
	(void)command;
	return (0);
}

int ft_get_parameter(char* substr, t_com *command)
{
	(void)substr;
	(void)command;
	return (0);
}

int ft_get_variable(char* substr, t_com *command)
{
	(void)substr;
	(void)command;
	return (0);
}

int	first_word_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] && !ft_isspace(str[len]))
		len++;
	return (len);
}

int ft_get_arg(char* substr, t_com *command)
{
	char	*str;
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	tmp = command->command;
	len = first_word_len(substr);
	str = malloc(sizeof(char) * (len + 2));
	if (!str)
		ft_exit_error("Memory Allocation Error\n");
	while (i < len)
	{
		str[i] = substr[i];
		i++;
	}
	str[i] = ' ';
	i++;
	str[i] = '\0';
	command->command = ft_strjoin(command->command, str);
	free(str);
	free(tmp);
	return (len);
}

int	parse_commandline(t_data *data)
{
	int		returnval;
	int		i;

	returnval = 0;
	i = 0;
	data->command = ft_command_init();
	while (data->command_line[i])
	{
		while(ft_isspace(data->command_line[i]))
			i++;
		if (data->command_line[i] == '<')
			i += ft_change_input(&data->command_line[i], data->command);
		else if (data->command_line[i] == '>')
			i += ft_change_output(&data->command_line[i], data->command);
		else if (data->command_line[i] == '"')
			i += ft_get_double_quote_arg (&data->command_line[i], data->command);
		else if (data->command_line[i] == '\'')
			i += ft_get_quote_arg (&data->command_line[i], data->command);
		else if (data->command_line[i] == '-')
			i += ft_get_parameter(&data->command_line[i], data->command);
		else if (data->command_line[i] == '$')
			i += ft_get_variable(&data->command_line[i], data->command);
		else
			i += ft_get_arg(&data->command_line[i], data->command);
		i++;
	}
	return (returnval);
}



