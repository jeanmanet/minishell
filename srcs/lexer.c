/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:06:37 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/09 08:33:35 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lexing(char c)
{
	if (ft_isspace(c))
		return(LEX_SPACE);
	else if (c == '<')
		return(LEX_SMALLER);
	else if (c == '>')
		return (LEX_GREATER);
	else if (c == '|')
		return (LEX_PIPE);
	else if (c == '\'')
		return(LEX_SQUOTE);
	else if (c == '"')
		return (LEX_DQUOTE);
	return(LEX_WORD);
}


