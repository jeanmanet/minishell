#include "../includes/minishell.h"



int	lunch_commandline(char *str, char **envp)
{
	char	**cmd;
	pid_t	pid;

	cmd = get_current_command(str, envp);


	pid = fork();
	if (pid == 0)
		execve(cmd[0], cmd, envp);
	else
		wait(NULL);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char *str;

	(void)argc;
	(void)argv;
	while (1)
	{
		str = readline("minishell > ");
		if (!ft_strncmp(str, "exit", 4))
			exit (0);
		else
			lunch_commandline(str, envp);
	}
	return (0);

}
