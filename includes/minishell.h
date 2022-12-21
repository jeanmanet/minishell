/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:09:47 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/21 19:54:31 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct t_com
{
	char	*command;
	char	*infile;
	int		infile_mod;
	char	*delimiter;
	char	*outfile;
	int		outfile_mod;
	FILE	*input;
	FILE	*output;
}t_com;

typedef struct t_data
{
	char	*command_line;
	char	**envp;
	t_com	*command;

}	t_data;




char	**get_current_command(char	*arg, char **envp);
char	**ft_import_envp(char **envp, t_data *data);

char	*ft_getenv(char *name, t_data *data);
int		ft_setenv(char *name, char *value, int overwrite, t_data *data);
int		ft_change_directory(t_data *data);
int		parse_commandline(t_data *data);
int		exec_command(t_data *data);
int		cmd_is_builtin(t_data *data);
int		exec_builtin(t_data *data);
void	exit_cmd_strerror(char *cmd_name);
void	cmd_not_found(char *cmd_name);
void	ft_exit_error(char *error_msg);
void	free_tab_str(char **str);
#endif
