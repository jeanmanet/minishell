/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 12:01:57 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/01 12:53:09 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_name(char *str)
{
	int		i;
	char	*varname;

	i = 0;
	varname = NULL;
	while (str[i] && str[i] != '$')
		i++;
	varname = malloc(sizeof(char) * (i + 1));
	if (!varname)
		ft_exit_error("Memory Allocation Error !\n");
	i = 0;
	while (str[i] && str[i] != '$')
	{
		varname[i] = str[i];
		i++;
	}
	varname[i] = '\0';
	return (varname);
}

char	*init_str(void)
{
	char	*str;

	str = malloc(0);
	if (!str)
		ft_exit_error("Memory Allocation Error !\n");
	str[0] = '\0';
	return (str);
}

char	*expand_vars_in_token(char *token, t_data *data)
{
	int		i;
	char	*new_token;
	char	*temp;
	char	*varname;

	i = 0;
	new_token = init_str();
	while (token[i])
	{
		temp = new_token;
		if (token[i] == '$')
		{
			varname = get_var_name(&token[i + 1]);
			new_token = ft_strjoin(temp,
					get_var_value_in_varlist(varname, data->var_list));
			free(varname);
			while (token[i + 1] && token[i + 1] != '$')
				i++;
		}
		else
			new_token = ft_strjoin(temp, ft_substr(token, i, 1));
		free(temp);
		i++;
	}
	return (new_token);
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
				newtoken = expand_vars_in_token(tokenlist->token, data);
				free(tokenlist->token);
				tokenlist->token = newtoken;
			}
		}
		tokenlist = tokenlist->next;
	}
}
