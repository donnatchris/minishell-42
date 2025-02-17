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

// prototypes

t_dclst	**tokenize(char *input);
int		get_token(char **ps, char *es, char **q, char **eq);
void	clear_dclst_data(t_dclst **head);
int		check_syntax(t_dclst **head);

#endif