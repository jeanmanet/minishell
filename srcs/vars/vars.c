/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:21:31 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/01 11:02:18 by jmanet           ###   ########.fr       */
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

void	add_var_in_locallist(t_data *data)
{
	char	*varname;
	char	*varvalue;

	varname = get_var_name_in_token_list(data->token_list->token);
	varvalue = get_var_value_in_tokenlist(data->token_list);
	if (var_exist_in_locallist(varname, data->var_list))
		edit_variable(&data->var_list, varname, varvalue);
	else
		add_variable(&data->var_list, varname, varvalue);
	free(varname);
	free(varvalue);
}

void	ft_add_var(t_data *data)
{
	t_token_node	*list_tokens;

	list_tokens = data->token_list;
	while (list_tokens)
	{
		if (list_tokens->type == T_PIPE)
			list_tokens = list_tokens->next;
		if (token_is_in_quote(list_tokens) && list_tokens->type == T_ARG)
		{
			if (ft_ischarset(list_tokens->token, '='))
			{
				list_tokens->type = T_VAR;
				if (list_tokens->next && token_is_in_quote(list_tokens->next))
				{
					if (list_tokens->token[ft_strlen(list_tokens->token) - 1]
						== '=')
						list_tokens->next->type = T_VAR;
				}
			}
		}
		while (list_tokens && list_tokens->type != T_PIPE)
			list_tokens = list_tokens->next;
	}
	if (tokenlist_contains_only_vars(data))
		add_var_in_locallist(data);
}
