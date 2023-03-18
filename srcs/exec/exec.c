/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:05:35 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/19 00:17:39 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_pipe_node(t_ast_node *node);

int	execute_cmd_node(t_ast_node *node)
{
	exec_command(node->content->cmd);
	return (0);
}

int	execute_left_node(t_ast_node *left, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		return (-1);
	}
	else if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		if (left->type == AST_CMD)
			execute_cmd_node(left);
		else
			execute_pipe_node(left);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

void	execute_right_node(t_ast_node *right, int *pipe_fd)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	execute_cmd_node(right);
}

int	execute_pipe_node(t_ast_node *node)
{
	int		pipe_fd[2];
	pid_t	pid2;

	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe");
		return (-1);
	}
	execute_left_node(node->content->pipe->left, pipe_fd);
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("Fork");
		return (-1);
	}
	else if (pid2 == 0)
	{
		execute_right_node(node->content->pipe->right, pipe_fd);
		exit(0);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid2, NULL, 0);
	return (0);
}

int	execute_ast(t_data *data)
{
	if (data->commands_tree->root)
	{
		if (data->commands_tree->root->type == AST_CMD)
			execute_cmd_node(data->commands_tree->root);
		else
			execute_pipe_node(data->commands_tree->root);
	}
	return (0);
}
