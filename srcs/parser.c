/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:55:24 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/29 08:19:10 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*first_word(char *str)
{
	int	i;
	int	j;
	char *word;

	i = 0;
	j = 0;
	while (ft_isspace(str[i]))
		i++;
	while(!ft_isspace(str[j + i]) && str[j + i])
		j++;
	word = malloc(sizeof(*word) * (j + 1));
	if (!word)
		ft_exit_error("Memory Allocation Error\n");
	j = 0;
	while (!ft_isspace(str[j + i]) && str[j + i])
	{
		word[j] = str[j + i];
		j++;
	}
	word[j] = '\0';
	return (word);
}

int	get_quote_len(char	*str)
{
	int		i;
	char	c;

	i = 0;
	c = str[i];
	i++;
	while (str[i] != c && str[i])
		i++;
	while (!ft_isspace(str[i]))
		i++;
	return (i);
}

char	*ft_get_quote_arg(char *substr)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	i++;
	len = get_quote_len(substr);
	str = malloc(sizeof(*str) * (len + 1));
	if (!str)
		ft_exit_error("Memory Allocation Error\n");
	while (i < len)
	{
		str[i] = substr[i];
		i++;
	}
	str[i] = '\0';
	printf("str : %s\n", str);
	return (str);
}

int	ft_nbargs(char *command_line)
{
	int		i;
	char	c;
	int 	nbargs;

	i = 0;
	nbargs = 0;
	while (command_line[i])
	{
		if(command_line[i] == '"' || command_line[i] == '\'')
		{
			nbargs++;
			c = command_line[i++];
			while (command_line[i] != c)
				i++;
		}
		else if(!ft_isspace(command_line[i]) && command_line [i])
		{
			nbargs++;
			while(!ft_isspace(command_line[i]) && command_line [i])
				i++;
		}
		i++;
	}
	return (nbargs);
}

void	ft_command_line_to_args(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->command_line[i])
	{
		if(data->command_line[i] == '"' || data->command_line[i] == '\'')
		{
			data->args[j] = ft_get_quote_arg(&data->command_line[i]);
			i += ft_strlen(data->args[j++]);
		}
		else if(!ft_isspace(data->command_line[i]) && data->command_line [i])
		{
			data->args[j] = first_word(&data->command_line[i]);
			i += ft_strlen(data->args[j++]);
		}
		i++;
	}
	data->args[j] = NULL;
	free (data->command_line);
}

void	ft_print_args(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("args[%d] : %s \n", i, str[i]);
		i++;
	}
}

void	ft_make_command(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->args[i])
	{
		if (data->args[i][0] == '<')
		{
			data->command->infile = ft_strdup(data->args[i + 1]);
			i += 2;
		}
		else if (data->args[i][0] == '>')
		{
			data->command->outfile = ft_strdup(data->args[i + 1]);
			i += 2;
		}
		else if (!ft_strncmp(data->args[i], "|", 2))
		{
			break;
		}
		else
		{
			data->command->args[j] = ft_strdup(data->args[i]);
			j++;
			i++;
		}
	}
	data->command->args[j] = NULL;
}

void	ft_init_command(t_data *data)
{
	data->command->infile = malloc(sizeof(char*));
	ft_bzero(data->command->infile, sizeof(char*));
	data->command->outfile = malloc(sizeof(char*));
	ft_bzero(data->command->outfile, sizeof(char*));
	data->command->args = malloc(sizeof(char*) * (data->nbargs + 1));
	if (!data->command->args)
		ft_exit_error("Memory Allocation Error\n");
	//data->command->fd_input = 1;
	//data->command->fd_output = 1;
}

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

void	ft_free_allocated_mem(t_data *data)
{
	(void)data;
}



int	parse_commandline(t_data *data)
{
	int		returnval;

	returnval = 0;
	data->nbargs = ft_nbargs(data->command_line);
	data->args = malloc(sizeof(char*) * (data->nbargs + 1));
	ft_command_line_to_args(data);
//	ft_print_args(data->args);
	data->nbcmds = ft_get_nbcmds(data->args);
	ft_init_command(data);
	ft_make_command(data);
	returnval =	exec_command(data);
	ft_free_allocated_mem(data);
//	free_tab_str(data->args);
	return (returnval);
}



