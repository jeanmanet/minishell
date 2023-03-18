/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:51:45 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/18 21:00:46 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token_node **list_head) {
	t_token_node *current_node = *list_head;
	while (current_node != NULL) {
		t_token_node *temp_node = current_node;
		current_node = current_node->next;
		free(temp_node->token);
		free(temp_node);
	}
	*list_head = NULL;
}

void	free_cmd_node(t_ast_node	*cmd_node)
{
	free(cmd_node->content->cmd->args);
	free(cmd_node->content->cmd);
	free(cmd_node->content);
}

void	free_ast(t_ast	*ast_tree)
{
	if (ast_tree->root->type == AST_CMD)
	{
		free_cmd_node(ast_tree->root);
		// free(ast_tree->root->content->cmd->args);
		// free(ast_tree->root->content->cmd);
		// free(ast_tree->root->content);
	}
	free(ast_tree->root);
	ast_tree->root = NULL;
}

void	free_mem(t_data *data)
{
	free(data->command_line);
    free_tokens(&data->token_list);
    free_ast(data->commands_tree);
    // if (data->command->args)
    //     free(data->command->args);
}
