/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:06:37 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/03 19:22:58 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lexing(char c)
{
	if (ft_isspace(c))
		return(SPACE);
	else if (c == '<')
		return(SMALLER);
	else if (c == '>')
		return (GREATER);
	else if (c == '|')
		return (PIPE);
	return(WORD);
}


