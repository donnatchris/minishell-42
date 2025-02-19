#ifndef MINISHELL_DEFINES_H
# define MINISHELL_DEFINES_H

// defines
# define SYMBOLS "<>|&;()'\""
# define WHITESPACES " \t\n\r\v\f"

typedef struct s_token
{
	int		type;
	int		priority;
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
