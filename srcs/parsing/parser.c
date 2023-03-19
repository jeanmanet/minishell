/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:26:37 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/19 11:42:03 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_com	*current_command_init(t_token_node *token_list)
{
	t_com	*cmd;
	char **args;
	int	i;

	i = 0;
	while(token_list && token_list->type != T_PIPE)
	{
		if (token_list->type == T_ARG)
			i++;
		token_list = token_list->next;
	}

	cmd = malloc(sizeof(t_com));
	args = malloc(sizeof(char *) * (i + 1));
	if (!cmd || !args)
		ft_exit_error("Memory Allocation Error \n");
	cmd->args = args;
	return (cmd);
}

t_union	*	init_cmd_union(t_com *command)
{
	t_union	*cmd_union;

	cmd_union = malloc(sizeof(t_union));
	if (!cmd_union)
		ft_exit_error("Memmory allocation error \n");
	cmd_union->cmd = command;
	return (cmd_union);
}

t_union	*	init_pipe_union(void)
{
	t_union	*pipe_union;
	t_pipe	*pipe_node;

	pipe_union = malloc(sizeof(t_union));
	pipe_node = malloc(sizeof(t_pipe));
	if (!pipe_union || !pipe_node)
		ft_exit_error("Memmory allocation error \n");
	pipe_union->pipe = pipe_node;
	pipe_union->pipe->left = NULL;
	pipe_union->pipe->right = NULL;
	return (pipe_union);
}

void	parse_token_list(t_data *data)
{
	t_com			*current_command;
	t_token_node	*token_list_head;
	int				i;

	token_list_head = data->token_list;
	i = 0;
	current_command = current_command_init(token_list_head);
	while (token_list_head)
	{
		if (token_list_head->type == T_ARG)
		{
			current_command->args[i++] = token_list_head->token;
			token_list_head = token_list_head->next;
		}
		else if (token_list_head->type == T_PIPE)
		{
			current_command->args[i] = NULL;
			token_list_head = token_list_head->next;
			add_ast_node(data, init_cmd_union(current_command), AST_CMD);
			add_ast_node(data, init_pipe_union(), AST_PIPE);
			current_command = current_command_init(token_list_head);
			i = 0;
		}
		else
			token_list_head = token_list_head->next;
	}
	current_command->args[i] = NULL;
	add_ast_node(data, init_cmd_union(current_command), AST_CMD);
}
