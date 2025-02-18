#ifndef MINISHELL_H
# define MINISHELL_H

// libraries
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>

// headers
# include "../../libft/headers/libft_H/libft.h"
# include "../../libft/headers/ft_printf_H/ft_printf.h"
# include "../../dclst/dclst.h"
# include "minishell_defines.h"

// prototypes
/* ************************************************************************** */
/*                                       parser                               */
/* ************************************************************************** */
t_dclst	**tokenize(char *input);
int		get_token(char **ps, char *es, char **q, char **eq);
void	clear_dclst_data(t_dclst **head);
int		check_syntax(t_dclst **head);
t_tree	*create_tree(t_dclst *first, t_dclst *last);
void	clear_tree(t_tree *root);
void	print_tree(t_tree *root); // A retirer avant de rendre
void	print_a_token(t_token *token); // A retirer avant de rendre

#endif