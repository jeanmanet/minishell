/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:46:19 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/29 09:48:03 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// fonction utile pour le dev, mais a supprimer a la fin du projet...
void	ft_print_args(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("args[%d] : %s \n", i, str[i]);
		i++;
	}
}
/*-------------------------------------------------------------------------*/
