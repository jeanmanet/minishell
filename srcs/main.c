/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:03:37 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/20 13:33:46 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_commandline(t_data *data)
{
	char	**cmd;
	pid_t	pid;

	cmd = get_current_command(data->command_line, data->envp);
	if (cmd[0])
	{
		pid = fork();
		if (pid == 0)
			execve(cmd[0], cmd, data->envp);
		else
			wait(NULL);
	}
	free_tab_str(cmd);
	return (0);
}

int	parse_commandline(t_data *data)
{
	int	returnval;

	returnval = 0;
	if (ft_strlen(data->command_line))
	{
		if (cmd_is_builtin(data))
			returnval = exec_builtin(data);
		else
			returnval = exec_commandline(data);
	}
	free(data->command_line);
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

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.envp = ft_import_envp(envp, &data);
	if (argc > 1)
		ft_exec_scriptfile(argv);
	while (1)
	{
		signal(SIGSEGV, ft_signal_handler);
		signal(SIGINT, ft_signal_handler);
		signal(SIGQUIT, ft_signal_handler);
		data.command_line = readline("minishell > ");
		add_history(data.command_line);
		printf("returnval : %d\n", parse_commandline(&data));
	}
	return (0);

}
