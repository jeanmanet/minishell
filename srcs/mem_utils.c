/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:51:45 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/07 13:52:29 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_tokens(t_token_node **list_head) {
    t_token_node *current_node = *list_head;
    while (current_node != NULL) {
        t_token_node *temp_node = current_node;
        current_node = current_node->next;
        free(temp_node->token);
        free(temp_node);
    }
    *list_head = NULL;
}

void	free_mem(t_data *data)
{
	free(data->command_line);
    free_tokens(&data->token_list);
    if (data->command->args)
        free(data->command->args);
}
