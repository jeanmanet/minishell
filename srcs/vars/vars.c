/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:21:31 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/09 09:48:54 by jmanet           ###   ########.fr       */
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

	varname = get_var_name_in_assignment(data->token_list->token);
	varvalue = get_var_value_in_tokenlist(data->token_list);
	if (var_exist_in_locallist(varname, data->var_list))
	{
		edit_variable(&data->var_list, varname, varvalue);
		if (var_is_in_env(varname, data->envp))
			export_local_var_to_env(varname, data);
	}
	else
		add_variable(&data->var_list, varname, varvalue);
	free(varname);
	free(varvalue);
}

int	token_contains_valid_variable(char *token)
{
	char	*varname;
	int		ret;

	ret = 0;
	if (ft_ischarset(token, '='))
	{
		varname = get_var_name_in_assignment(token);
		if (ft_strlen(varname))
			ret = 1;
		else
			ret = 0;
		free(varname);
	}
	return (ret);
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
			if (token_contains_valid_variable(list_tokens->token))
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

void	ft_update_local_exit_var(t_data *data)
{
	if (g_global.exit_code_error != 0)
		data->endstatus = g_global.exit_code_error;
	data->endvar = ft_itoa(data->endstatus);
	edit_variable(&data->var_list, "?", data->endvar);
}
