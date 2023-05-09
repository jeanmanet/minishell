/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:34:02 by ory               #+#    #+#             */
/*   Updated: 2023/05/09 12:33:17 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	token_type_is_redir(t_token_node *token_list)
{
	if (!token_list)
		return (0);
	if (token_list->type == T_REDIR_IN)
		return (1);
	if (token_list->type == T_REDIR_OUT)
		return (1);
	if (token_list->type == T_PIPE)
		return (1);
	return (0);
}

int	check_next_redir_token(t_token_node *token_list)
{
	if (!token_list)
	{
		g_global.exit_code_error = 258;
		printf("syntax error: unexpected token `newline'\n");
		return (1);
	}
	else
	{
		if (!token_type_is_redir(token_list->next))
		{
			g_global.exit_code_error = 258;
			printf("syntax error: unexpected token `%s'\n",
				token_list->token);
			return (1);
		}
	}
	return (0);
}

int	check_next_pipe_token(t_token_node *token_list)
{
	if (!token_list->next)
	{
		g_global.exit_code_error = 258;
		printf("syntax error: unexpected token `newline'\n");
		return (1);
	}
	if (!token_list->prev)
	{
		g_global.exit_code_error = 258;
		printf("syntax error: unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int	check_unexpected_token(t_token_node *token_list)
{
	int	ret;

	ret = 0;
	while (token_list)
	{
		if (token_list->type == T_REDIR_IN || token_list->type == T_REDIR_OUT)
			ret = check_next_redir_token(token_list->next);
		else if (token_list->type == T_PIPE)
			ret = check_next_pipe_token(token_list);
		if (ret)
			return (ret);
		token_list = token_list->next;
	}
	return (0);
}
