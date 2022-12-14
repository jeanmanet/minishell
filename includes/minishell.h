/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:09:47 by jmanet            #+#    #+#             */
/*   Updated: 2022/12/29 10:36:11 by jmanet           ###   ########.fr       */
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
	char	**args;
	char	*infile;
	char	*outfile;
	//int		fd_input;// 1 pour std, 2 pour fichier, 3 pour pipe;
	//int		fd_output;// 1 pour std, 2 pour fichier, 3 pour pipe;

}t_com;

typedef struct t_var
{
	char	*name;
	char	*value;
}t_var;

typedef struct t_data
{
	char	*command_line;
	char	**envp;
	char	**args;
	int		nbargs;
	int		nbcmds;
	int		endstatus;
	t_com	*command;

}	t_data;

char	*get_current_command(char	*arg, char **envp);
char	**ft_import_envp(char **envp, t_data *data);

char	*ft_getenv(char *name, t_data *data);
int		ft_setenv(char *name, char *value, int overwrite, t_data *data);
int		ft_change_directory(t_data *data);
int		parse_commandline(t_data *data);
int		exec_command(t_data *data);
int		exec_processus(t_data *data);
int		cmd_is_builtin(t_data *data);
int		exec_builtin(t_data *data);
void	exit_cmd_strerror(char *cmd_name);
void	cmd_not_found(char *cmd_name);
void	ft_exit_error(char *error_msg);
int		ft_redirect_io(t_data *data);
int		open_infile(t_data *data);
int		open_outfile(t_data *data);
void	ft_signal_handler(int sig);
void	ft_exec_scriptfile(char **argv);
int		ft_nbargs(char *command_line);
void	ft_command_line_to_args(t_data *data);
void	ft_make_command(int cmd_number, t_data *data);
void	ft_free_allocated_mem(t_data *data);
void	ft_parse_args(t_data *data);
void	ft_free_command(t_data *data);


void	ft_print_args(char **str);
#endif
