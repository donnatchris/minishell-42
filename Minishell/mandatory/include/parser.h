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

typedef struct s_token
{
	int		type;
	int		priority;
	char	*start;
	char	*end;
}			t_token;

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
	TOKEN_REDIR_OUT,	// >
	TOKEN_APPEND,		// >>
	TOKEN_REDIR_IN,		// <
	TOKEN_HEREDOC,		// <<
	TOKEN_PIPE,			// |
	TOKEN_AND,			// &&
	TOKEN_OR,			// ||
	TOKEN_SEMICOLON,	// ;
	TOKEN_STRING,		// "texte" (variable autorisée)
	TOKEN_WORD,			// Un mot
	TOKEN_LITTERAL,		// 'texte' (pas de variable)
	TOKEN_EOF,			// Fin d'entrée
	TOKEN_ERROR			// Erreur
}	t_token_type;

// prototypes

t_dclst	**tokenize(char *input);
int		get_token(char **ps, char *es, char **q, char **eq);
void	clear_dclst_data(t_dclst **head);

#endif