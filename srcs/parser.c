/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:55:24 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/07 13:55:21 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int get_inquote_token(char *str)
// {

// }

int	get_next_token(char *str)
{
	int	i;

	i = 0;
	if (str[i] && ft_lexing(str[i]) == PIPE)
		return (1);
	if (str[i] && ft_lexing(str[i]) == GREATER)
	{
		if (ft_lexing(str[i + 1]) == GREATER)
			return (2);
		else
			return (1);
	}
	if (str[i] && ft_lexing(str[i]) == SMALLER)
	{
		if (ft_lexing(str[i + 1]) == SMALLER)
			return (2);
		else
			return (1);
	}
	// if (str[i] && (ft_lexing(str[i]) == SQUOTE || ft_lexing(str[i]) == DQUOTE))
	// 	i = get_inquote_token(str);
	else if (str[i] && ft_lexing(str[i]) == WORD)
		while (str[i] && ft_lexing(str[i]) == WORD)
			i++;
	return (i);
}

t_token_node *parse_commandline(char *commandline)
{
	t_token_node *token_list = NULL;
	char *temp;
	int	start;
	size_t	len;
	start = 0;
	len = 0;

	while (commandline[start])
	{
		if(ft_lexing(commandline[start]) <= DQUOTE)
		{
			len = get_next_token(&commandline[start]);
			temp = ft_substr(commandline, start, len);
			start += (int)len;
			add_token_node(&token_list, temp);
			free(temp);
		}
		else
		{
			start++;
			len = 0;
		}
	}
	return (token_list);
}
