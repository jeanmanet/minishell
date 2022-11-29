#include "../includes/minishell.h"



int	launch_commandline(t_data *data)
{
	char	**cmd;
	pid_t	pid;

	cmd = get_current_command(data->str, data->envp);
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






void	ft_get_stdin(t_data *data)
{
	//char	**split_str;

	if (data->str[0] == '<')
	{
		data->in_isinfile = 1;
		//splitstr = ft_split(data->)

	}
	else
		data->in_isinfile = 0;
}

int	parse_commandline(t_data *data)
{
	if (ft_strlen(data->str))
	{
		if (!cmd_is_builtin(data))
		{
			ft_get_stdin(data);
			launch_commandline(data);
		}
	}
	free(data->str);
	return (0);
}


void	ft_nothing(int sig)
{
		//printf("numero du signal %d\n", sig);
		if (sig == 11)
		{
			printf("exit\n");
			exit (0);
		}
		if (sig == 2)
			printf("\n");
}



int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1)
		exit (0);
	(void)argv;
	data.envp = ft_import_envp(envp, &data);

	//signal(SIGABRT, ft_nothing);
	while (1)
	{
		signal(SIGSEGV, ft_nothing);
		signal(SIGINT, ft_nothing);
		signal(SIGQUIT, ft_nothing);
		data.str = readline("minishell > ");
		add_history(data.str);
		parse_commandline(&data);
	}
	return (0);

}
