/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:59:26 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/09 15:18:45 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_pwd(t_data *data)
{
	char	*pwd;

	pwd = get_var_value_in_varlist("PWD", data->var_list);
	printf("%s\n", pwd);
	return (0);
}
