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

// structures
typedef struct s_token
{
	int		type;
	int		priority;
	int		space;
	char	*start;
	char	*end;
}			t_token;

typedef struct s_tree
{
	t_token			*token;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef enum e_token_type
{
	NOTHING,			// Rien (pour ne pas utiliser la valeur zéro)
	TOKEN_PARENTHESIS,	// (...) / Prio1
	TOKEN_REDIR_OUT,	// > / Prio2
	TOKEN_APPEND,		// >> / Prio2
	TOKEN_REDIR_IN,		// < / Prio2
	TOKEN_HEREDOC,		// << / Prio2
	TOKEN_PIPE,			// | / Prio3
	TOKEN_AND,			// && / Prio4
	TOKEN_OR,			// || / Prio4
	TOKEN_SEMICOLON,	// ;  / Prio5
	TOKEN_STRING,		// "texte" (variable autorisée) / Prio6
	TOKEN_WORD,			// Un mot (variable autorisée) / Prio6
	TOKEN_LITTERAL,		// 'texte' (pas de variable) / Prio6
	TOKEN_EOF,			// Fin d'entrée
	TOKEN_ERROR			// Erreur
}	t_token_type;

#endif
