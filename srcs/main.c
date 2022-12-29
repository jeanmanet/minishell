/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:03:37 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/28 19:48:25 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int	exec_processus(t_data *data)
{
	pid_t	pid;
	char	**cmd;

	cmd = data->command->args;
	cmd[0] = get_current_command(cmd[0], data->envp);
	if (cmd[0])
	{
		pid = fork();
		if (pid == 0)
		{
			ft_redirect_io(data);
			execve(cmd[0], cmd, data->envp);
		}
		else
			wait(NULL);
	}
	return (0);
}


int	exec_command(t_data *data)
{
	int	returnval;
	returnval = 0;
	//printf("args 0 : %s\n", data->command->args[0]);
	if (data->command->args[0] != NULL)
	{
		if (cmd_is_builtin(data))
		{
			ft_redirect_io(data);
			returnval = exec_builtin(data);
			dup2(0,1);
		}
		else
		{
			//printf("is cmd \n");
			//ft_print_args(data->command->args);
			returnval = exec_processus(data);
		}
	}
	return (returnval);
}

void	ft_signal_handler(int sig)
{
		//printf("numero du signal %d\n", sig);
		if (sig == 11)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		if (sig == 2)
			printf("\n");
}

void	ft_exec_scriptfile(char **argv)
{
	//developper le code qui execute le contenu du fichier script
	//ouvrir le fichier
	//getnextline
	//etc...
	//sortir proprement apres avoir libere toutes les variables allouees dynamiquement
	(void)argv;
	exit(0);
}

void	ft_free_args(t_data *data)
{
	int	i;

	i = 0;
	while (data->args[i])
	{
		free(data->args[i]);
		i++;
	}
	free(data->args);
}





int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(*data));
	data->command = malloc(sizeof(data->command));
	data->envp = ft_import_envp(envp, data);
	if (argc > 1)
		ft_exec_scriptfile(argv);
	while (1)
	{
		//signal(SIGSEGV, ft_signal_handler);
		//signal(SIGINT, ft_signal_handler);
		//signal(SIGQUIT, ft_signal_handler);
		data->command_line = readline("minishell > ");
		add_history(data->command_line);
		parse_commandline(data);
		//ft_free_args(data);
	}
	return (0);

}
