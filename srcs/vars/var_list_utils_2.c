/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:19:46 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/09 15:20:27 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	var_is_protected(char *varname)
{
	if (!ft_strncmp(varname, "?", 2))
		return (1);
	if (!ft_strncmp(varname, "OLDPWD", 7))
		return (1);
	if (!ft_strncmp(varname, "PWD", 4))
		return (1);
	if (!ft_strncmp(varname, "pwd", 4))
		return (1);
	return (0);
}
