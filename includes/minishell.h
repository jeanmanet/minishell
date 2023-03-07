/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:09:47 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/07 13:54:27 by jmanet           ###   ########.fr       */
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
	int		cmd_input;
	int		cmd_output;
}t_com;

enum	e_lexer_type{
	WORD,
	SMALLER,
	GREATER,
	PIPE,
	SQUOTE,
	DQUOTE,
	SPACE
};

enum	e_cmd_io{
	STDIN,
	STDOUT,
	INFILE,
	HERE_DOC,
	APPEND,
	TRUNC
};

typedef struct t_token_node {
    char *token;
    struct t_token_node *next;
    struct t_token_node *prev;
} t_token_node;

typedef struct t_data
{
	t_token_node *token_list;
	char	*command_line;
	char	**envp;
	int		endstatus;
	t_com	*command;

}	t_data;

char	*get_current_command(char	*arg, char **envp);
char	**ft_import_envp(char **envp, t_data *data);

char	*ft_getenv(char *name, t_data *data);
int		ft_setenv(char *name, char *value, int overwrite, t_data *data);
int		ft_change_directory(t_data *data);
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
void	ft_free_command(t_data *data);


void	build_command(t_data *data);
int		ft_lexing(char c);


t_token_node *create_token_node(char *token);
void add_token_node(t_token_node **list_head, char *token);
void print_tokens(t_token_node *list_head);

t_token_node *parse_commandline(char *commandline);

void	free_mem(t_data *data);
#endif
