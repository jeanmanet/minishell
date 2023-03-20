/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:09:47 by jmanet            #+#    #+#             */
/*   Updated: 2023/03/20 09:00:22 by jmanet           ###   ########.fr       */
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

enum	e_lexer_type{
	LEX_WORD,
	LEX_SMALLER,
	LEX_GREATER,
	LEX_PIPE,
	LEX_SQUOTE,
	LEX_DQUOTE,
	LEX_SPACE
};

enum	e_cmd_io{
	CMD_STDIN,
	CMD_STDOUT,
	CMD_INFILE,
	CMD_HERE_DOC,
	CMD_APPEND,
	CMD_TRUNC
};

enum	e_token_state{
	S_IN_SQUOTE,
	S_IN_DQUOTE,
	S_NOT_IN_QUOTE
};

enum	e_token_type{
	T_ARG,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_PIPE
};

enum e_ast_node_type{
	AST_CMD,
	AST_PIPE
};

typedef struct t_token_node {
    char	*token;
	int		q_state;
	int		type;
    struct t_token_node *next;
    struct t_token_node *prev;
} t_token_node;

typedef struct t_com
{
	char	**args;
	char	*infile;
	char	*outfile;
	int		cmd_input;
	int		cmd_output;
}t_com;

typedef struct s_ast_node	t_ast_node;

typedef struct t_pipe
{
	t_ast_node	*left;
	t_ast_node	*right;
}t_pipe;

typedef union t_union
{
	t_pipe	*pipe;
	t_com	*cmd;
}t_union;

typedef struct s_ast_node
{
	enum e_ast_node_type	type;
	t_union				*content;
}t_ast_node;


typedef struct t_ast
{
	t_ast_node	*root;
}	t_ast;



typedef struct t_data
{
	t_token_node *token_list;
	t_ast	*commands_tree;
	char	*command_line;
	char	**envp;
	int		endstatus;
	t_com	*command;

}	t_data;

char	*get_absolute_command(char	*arg, char **envp);
char	**ft_import_envp(char **envp);

char	*ft_getenv(char *name, t_data *data);
int		ft_setenv(char *name, char *value, int overwrite, t_data *data);
int		ft_change_directory(t_com *command, t_data *data);
int		exec_command(t_com *command, t_data *data);
int		exec_processus(t_com *command, t_data *data);
int		cmd_is_builtin(t_com *command);
int		exec_builtin(t_com *command, t_data *data);
void	exit_cmd_strerror(char *cmd_name);
void	cmd_not_found(char *cmd_name);
void	ft_exit_error(char *error_msg);
int		ft_redirect_io (t_com *command, t_data *data);
int		open_infile(t_data *data);
int		open_outfile(t_data *data);
void	ft_signal_handler(int sig);


void	parse_token_list(t_data *data);
int		ft_lexing(char c);
int	execute_ast(t_data *data);

t_token_node *create_token_node(char *token, int state);
void add_token_node(t_token_node **list_head, char *token, int state);
void print_tokens(t_token_node *list_head);

t_token_node *tokenizer(char *commandline);
void	add_ast_node(t_data *data, t_union *content, int type);

void	free_mem(t_data *data);

t_union	*init_cmd_union(t_com *command);
t_union	*init_pipe_union(void);
#endif
