#ifndef MINISHELL_DEFINES_H
# define MINISHELL_DEFINES_H

// defines
# define SYMBOLS "<>|&;()'\""
# define WHITESPACES " \t\n\r\v\f"

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
typedef struct s_token
{
	int		type;
	int		priority;
	int		space;
	char	*start;
	char	*end;
}			t_token;

typedef enum e_token_type
{
	NOTHING,			// Rien (pour ne pas utiliser la valeur zéro)
	TOKEN_PARENTHESIS,	// (...) / Prio1
	TOKEN_PIPE,			// | / Prio2
	TOKEN_AND,			// && / Prio3
	TOKEN_OR,			// || / Prio3
	TOKEN_REDIR_OUT,	// > / Prio4
	TOKEN_APPEND,		// >> / Prio4
	TOKEN_REDIR_IN,		// < / Prio4
	TOKEN_HEREDOC,		// << / Prio4
	TOKEN_SEMICOLON,	// ;  / Prio5
	TOKEN_STRING,		// "texte" (variable autorisée) / Prio6
	TOKEN_WORD,			// Un mot (variable autorisée) / Prio6
	TOKEN_LITTERAL,		// 'texte' (pas de variable) / Prio6
	TOKEN_EOF,			// Fin d'entrée
	TOKEN_ERROR			// Erreur
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
	TREE_NOTHING,		// Rien (pour ne pas utiliser la valeur zéro)
	TREE_PARENTHESIS,	// Parenthèses
	TREE_PIPE,			// Pipe
	TREE_AND,			// Et
	TREE_OR,			// Ou
	TREE_SEMICOLON,		// Séparateur
	TREE_COMMAND,		// Commande simple
	TREE_ERROR			// Erreur
}	t_tree_type;

typedef struct s_general
{
	char	*pwd;
	char	*home;
	char	*input;
	char	*input_cpy;
	char	**envp;
	t_dclst	**head;
	t_tree	*tree;
	int		exit_status;
}			t_general;

# define NO_HIDDEN 0
# define W_HIDDEN 1
# define NO_PARENTHESIS 0
# define IN_PARENTHESIS 1

#endif
