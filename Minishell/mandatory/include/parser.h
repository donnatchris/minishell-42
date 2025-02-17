#ifndef PARSER_H
# define PARSER_H

// includes

# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include "../../libft/headers/libft_H/libft.h"
# include "../../libft/headers/ft_printf_H/ft_printf.h"
# include "../../dclst/dclst.h"

// defines

# define SYMBOLS "<>|&;()'\""
# define WHITESPACES " \t\n\r\v\f"

// typedefs

typedef enum e_type
{
	CMD,
	PIPE,
	AND,
	OR,	
	SEQ
}	t_type;
/*
CMD = 0 représente une commande simple (ex: "ls -l")
PIPE = 1 représente l'opérateur "|"
AND = 2 représente l'opérateur "&&"
OR = 3 représente l'opérateur "||"
SEQ = 4 représente l'opérateur ";"
*/

typedef struct s_tree
{
	t_token				*token;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}						t_tree;
/*
type = CMD, PIPE, AND, OR, etc.
cmd = Commande si c'est une feuille (sinon NULL)
left = Pointeur vers le fils gauche (NULL pour une feuille)
right = Pointeur vers le fils droit (NULL pour une feuille)
*/
typedef enum e_token_type
{
	NOTHING,			// Rien (pour ne pas utiliser la valeur zéro)
	TOKEN_PARENTHESIS,	// (...)
	TOKEN_AND,			// &&
	TOKEN_OR,			// ||
	TOKEN_PIPE,			// |
	TOKEN_REDIR_OUT,	// >
	TOKEN_APPEND,		// >>
	TOKEN_REDIR_IN,		// <
	TOKEN_HEREDOC,		// <<
	TOKEN_SEMICOLON,	// ;
	TOKEN_STRING,		// "texte" (variable autorisée)
	TOKEN_WORD,			// Un mot
	TOKEN_LITTERAL,		// 'texte' (pas de variable)
	TOKEN_EOF,			// Fin d'entrée
	TOKEN_ERROR			// Erreur
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	int				priority;
	char			*start;
	char			*end;
}					t_token;


// prototypes
t_dclst	**tokenize_to_dclst(char *input);
int		get_token(char **ps, char *es, char **q, char **eq);
void	clear_dclst_data(t_dclst **head);

#endif