/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:01:57 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/30 12:43:07 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_vars_in_tokenlist(t_data *data)
{
	t_token_node	*tokenlist;
	int				i;

	tokenlist = data->token_list;
	while (tokenlist)
	{
		if (tokenlist->q_state != S_IN_SQUOTE)
		{
			while (tokenlist->token[i])
			{
				if (tokenlist->token[i] == '$')
					expand_var_in_token();
			}
		}
		tokenlist = tokenlist->next;
	}
}
