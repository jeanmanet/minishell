/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:55:24 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/09 11:12:39 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_inquote_token(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = str[i];
	while (str[i + 1] != c)
		i++;
	return (i + 2);
}

int	get_next_token(char *str)
{
	int	i;

	i = 0;
	if (str[i] && ft_lexing(str[i]) == LEX_PIPE)
		return (1);
	if (str[i] && (ft_lexing(str[i]) == LEX_GREATER
			|| ft_lexing(str[i]) == LEX_SMALLER))
	{
		if (ft_lexing(str[i + 1]) == ft_lexing(str[i]))
			return (2);
		else
			return (1);
	}
	if (str[i] && (ft_lexing(str[i]) == LEX_SQUOTE
			|| ft_lexing(str[i]) == LEX_DQUOTE))
		return (get_inquote_token(str));
	if (str[i] && ft_lexing(str[i]) == LEX_WORD)
		while (str[i] && ft_lexing(str[i]) == LEX_WORD)
			i++;
	return (i);
}

t_token_node	*parse_commandline(char *commandline)
{
	t_token_node	*token_list;
	char			*temp;
	int				start;
	size_t			len;

	start = 0;
	len = 0;
	token_list = NULL;
	while (commandline[start])
	{
		len = get_next_token(&commandline[start]);
		if (ft_lexing(commandline[start]) <= LEX_DQUOTE)
		{
			if (ft_lexing(commandline[start]) <= LEX_PIPE)
				temp = ft_substr(commandline, start, len);
			else
				temp = ft_substr(commandline, start + 1, len - 2);
			add_token_node(&token_list, temp, ft_lexing(commandline[start]));
			start += (int)len;
			free(temp);
		}
		else
			start++;
	}
	return (token_list);
}
