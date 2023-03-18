/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:24:38 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/18 12:45:31 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**malloc_command_tab(int nb_tokens)
{
	char	**command_tab;

	command_tab = malloc(sizeof(char *) * (nb_tokens + 1));
	if (!command_tab)
	{
		printf("Allocation memory error \n");
		exit(-1);
	}
	return (command_tab);
}

void	build_command(t_data *data)
{
	t_token_node	*token_list_head;
	int			i;

	i = 0;
	token_list_head = data->token_list;
	while(token_list_head)
	{
		i++;
		token_list_head = token_list_head->next;
	}
	printf("nombre de tokens dans la liste : %d\n", i);
	data->command->args = malloc_command_tab(i);
	token_list_head = data->token_list;
	i = 0;
	while(token_list_head)
	{
		data->command->args[i] = token_list_head->token;
		token_list_head = token_list_head->next;
		i++;
	}
	data->command->args[i] = NULL;
	data->command->args[0] = get_current_command(data->command->args[0], data->envp);
}
