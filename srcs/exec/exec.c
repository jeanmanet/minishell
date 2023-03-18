/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:05:35 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/18 20:32:35 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	execute_cmd(t_ast_node *node)
{
	char	**args;
	int		i;

	i = 0;
	args = node->content->cmd->args;
	printf("Execute CMD :\n");
	while (args[i])
	{
		printf("Arg num %d = %s\n", i, args[i]);
		i++;
	}
	return (i);
}

int	execute_pipe(t_ast_node *node)
{
	printf("Execute PIPE\n");

	if (node->content->pipe->left->type == AST_CMD)
	{
		execute_cmd(node->content->pipe->left);
		execute_cmd(node->content->pipe->right);
	}
	return (0);
}

int	execute_ast(t_data *data)
{
	if (data->commands_tree->root)
	{
		if (data->commands_tree->root->type == AST_CMD)
			execute_cmd(data->commands_tree->root);
		else
			execute_pipe(data->commands_tree->root);
	}
	return (0);
}
