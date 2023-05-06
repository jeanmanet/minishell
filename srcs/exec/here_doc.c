/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:36:48 by jmanet            #+#    #+#             */
/*   Updated: 2023/05/06 12:14:45 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_here_docfile(void)
{
	int	fd_here_doc;

	fd_here_doc = open(".here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_here_doc == -1)
	{
		printf("Error, cannot create here_doc.tmp \n");
		return (-1);
	}
	return (fd_here_doc);
}

char	*get_line_here_doc(char *prompt)
{
	char	*temp;

	if (!prompt)
		return (NULL);
	temp = prompt;
	prompt = ft_strjoin(temp, "\n");
	free(temp);
	return (prompt);
}

int	make_here_doc(t_com *command)
{
	int		fd_here_doc;
	char	*line;

	fd_here_doc = open_here_docfile();
	command->here_doc_limiter = command->infile;
	signal(SIGINT, ft_signal_handler_here_doc);
	signal(SIGQUIT, ft_signal_handler_here_doc);
	while (1)
	{
		line = readline("here_doc > ");
		line = get_line_here_doc(line);
		if (!line)
			break ;
		if (ft_strlen(line) == ft_strlen(command->here_doc_limiter) + 1)
			if (ft_strncmp(line, command->here_doc_limiter,
					ft_strlen(line) - 1) == 0)
				break ;
		ft_putstr_fd(line, fd_here_doc);
		free(line);
	}
	if (line)
		free(line);
	close(fd_here_doc);
	return (fd_here_doc);
}

int	make_here_doc_in_process(t_com *command)
{
	int	status;

	g_global.pid = fork();
	if (g_global.pid == 0)
	{
		make_here_doc(command);
		exit(0);
	}
	else
		waitpid(g_global.pid, &status, 0);
	g_global.pid = 0;
	return (WIFEXITED(status));
}

void	ft_make_here_doc(t_ast_node *node, t_data *data)
{
	if (node->type == AST_CMD)
	{
		if (node->content->cmd->cmd_input_mode == CMD_HERE_DOC)
			make_here_doc_in_process(node->content->cmd);
	}
	else
	{
		if (node->content->pipe->left->type == AST_PIPE)
			ft_make_here_doc(node->content->pipe->left, data);
		else
		{
			if (node->content->pipe->left->content->cmd->cmd_input_mode
				== CMD_HERE_DOC)
				make_here_doc_in_process
					(node->content->pipe->left->content->cmd);
		}
		if (node->content->pipe->right->content->cmd->cmd_input_mode
			== CMD_HERE_DOC)
			make_here_doc_in_process(node->content->pipe->right->content->cmd);
	}
}
