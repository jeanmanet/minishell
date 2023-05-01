/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:01:57 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/01 10:35:40 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_vars_in_token(char *token)
{
	// int	nbvars;
	// int	varlen;
	// int	valuelen;
	// int	i;

	(void)token;
	return (NULL);
}

void	expand_vars_in_tokenlist(t_data *data)
{
	t_token_node	*tokenlist;
	char			*newtoken;

	tokenlist = data->token_list;
	while (tokenlist)
	{
		if (tokenlist->q_state != S_IN_SQUOTE)
		{
			if (ft_ischarset(tokenlist->token, '$'))
			{
				newtoken = expand_vars_in_token(tokenlist->token);
				free(tokenlist->token);
				tokenlist->token = newtoken;
			}
		}
		tokenlist = tokenlist->next;
	}
}
