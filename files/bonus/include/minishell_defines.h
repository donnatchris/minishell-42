/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_defines.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 07:03:04 by christophed       #+#    #+#             */
/*   Updated: 2025/03/16 14:36:54 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINES_H
# define MINISHELL_DEFINES_H

// defines
# define SYMBOLS "<>|&;()'\""
# define WHITESPACES " \t\n\r\v\f"
# define NO_HIDDEN 0
# define W_HIDDEN 1
# define NO_PARENTHESIS 0
# define IN_PARENTHESIS 1
# define TEMP_FILE "/tmp/minishell_heredoc.tmp"

// Color definitions
# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

// Global variable
extern int	g_signals;

// structures and enums
typedef struct s_delim
{
	char	*str;
	int		is_litteral;
}			t_delim;

typedef struct s_token
{
	int		type;
	int		priority;
	int		space;
	char	*start;
	char	*end;
	int		str_is_malloc;
}			t_token;

typedef enum e_token_type
{
	NOTHING,
	TOKEN_PARENTHESIS,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_REDIR_IN,
	TOKEN_HEREDOC,
	TOKEN_SEMICOLON,
	TOKEN_STRING,
	TOKEN_WORD,
	TOKEN_LITTERAL,
	TOKEN_EOF,
	TOKEN_ERROR
}	t_token_type;

typedef struct s_tree
{
	int				type;
	t_dclst			*list_node;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef enum e_tree_type
{
	TREE_NOTHING,
	TREE_PARENTHESIS,
	TREE_PIPE,
	TREE_AND,
	TREE_OR,
	TREE_SEMICOLON,
	TREE_COMMAND,
	TREE_ERROR
}	t_tree_type;

typedef struct s_general
{
	char	*pwd;
	char	*home;
	char	*input;
	char	*in_start;
	char	*in_end;
	char	*input_cpy;
	char	**envp;
	t_dclst	**head;
	t_tree	*tree;
	int		exit_status;
	int		stdin_backup;
	int		stdout_backup;
	int		in_pipe;
}			t_general;

#endif