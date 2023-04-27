/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:40:33 by jmanet            #+#    #+#             */
/*   Updated: 2023/04/27 11:49:54 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	var_exist_in_locallist(char *varname, t_lst_var *var_list)
{
	while (var_list)
	{
		if (!ft_strncmp(varname, var_list->name, ft_strlen(varname)))
			return (1);
		var_list = var_list->next;
	}
	return (0);
}

char	*get_var_name(char *str)
{
	int		i;
	char	*varname;

	i = 0;
	if (!ft_ischarset(str, '='))
		return (NULL);
	while (str[i] != '=')
		i++;
	varname = malloc(sizeof(char) * i + 1);
	if (!varname)
		return (NULL);
	i = 0;
	while (str[i] != '=')
	{
		varname[i] = str[i];
		i++;
	}
	varname[i] = '\0';
	return (varname);
}

char	*get_var_value(t_token_node *tokenlist)
{
	int		i;
	char	*str;
	char	*varvalue;

	i = 0;
	str = tokenlist->token;
	varvalue = NULL;
	if (!ft_ischarset(str, '='))
		return (NULL);
	while (str[i] != '=')
		i++;
	i++;
	if (str[i])
		varvalue = ft_substr(str, i, ft_strlen(str + i));
	else
		if (tokenlist->next)
			varvalue = ft_strdup(tokenlist->next->token);
	return (varvalue);
}
