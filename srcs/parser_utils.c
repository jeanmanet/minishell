/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:41:20 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/29 10:03:36 by jmanet           ###   ########.fr       */
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
	data->nbargs = ft_nbargs(data->command_line);
	data->args = malloc(sizeof(char*) * (data->nbargs + 1));
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
