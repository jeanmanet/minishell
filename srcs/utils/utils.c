/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:58:08 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/01 18:44:38 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_with_char(char *str, char c)
{
	char	*str2;
	char	*str_joined;

	str2 = malloc(sizeof(char) * 2);
	if (!str2)
		ft_exit_error("Memory Allocation Error !\n");
	str2[0] = c;
	str2[1] = '\0';
	str_joined = ft_strjoin(str, str2);
	free(str2);
	return (str_joined);
}
