/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:21:31 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/25 12:55:06 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tokenlist_contains_only_vars(t_data *data)
{
	t_token_node	*list_tokens;

	list_tokens = data->token_list;
	while (list_tokens)
	{
		if (list_tokens->type != T_VAR)
			return (0);
		list_tokens = list_tokens->next;
	}
	return (1);
}

void	ft_add_var(t_data *data)
{
	t_token_node	*list_tokens;

	list_tokens = data->token_list;
	while (list_tokens)
	{
		if (list_tokens->q_state == S_NOT_IN_QUOTE
			&& list_tokens->type == T_ARG)
		{
			if (ft_ischarset(list_tokens->token, '='))
			{
				list_tokens->type = T_VAR;
				if (list_tokens->next
					&& list_tokens->next->q_state != S_NOT_IN_QUOTE)
					list_tokens->next->type = T_VAR;
				break ;
			}
		}
		list_tokens = list_tokens->next;
	}
	if (tokenlist_contains_only_vars(data))
		printf("Appel de la fonction qui ajoute la var dans la liste\n");
}
