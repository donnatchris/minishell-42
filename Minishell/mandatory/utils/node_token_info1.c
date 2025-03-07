/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_token_info1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:32:45 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 06:32:58 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Function to check if the token of the node is a logical operator
// (TOKEN_AND or TOKEN_OR or TOKEN_SEMICOLON)
// Returns 1 if the token is a logical operator, 0 otherwise
int	is_logical_operator(t_dclst *node)
{
	t_token	*tok;

	tok = (t_token *) node->data;
	if (tok->type == TOKEN_AND || tok->type == TOKEN_OR
		|| tok->type == TOKEN_SEMICOLON)
		return (1);
	return (0);
}

// Function to check if the token of the node is a parenthesis
// (TOKEN_PARENTHESIS)
// Returns 1 if the token is a parenthesis, 0 otherwise
int	is_parenthesis(t_dclst *node)
{
	t_token	*tok;

	tok = (t_token *) node->data;
	if (tok->type == TOKEN_PARENTHESIS)
		return (1);
	return (0);
}

// Function to check if the token of the node is the end of the list
// (TOKEN_EOF)
// Returns 1 if the token is the end of the list, 0 otherwise
int	is_eof(t_dclst *node)
{
	t_token	*tok;

	tok = (t_token *) node->data;
	if (tok->type == TOKEN_EOF)
		return (1);
	return (0);
}

// Functio  to check if the token of the node is a pipe
// (TOKEN_PIPE)
// Returns 1 if the token is a pipe, 0 otherwise
int	is_pipe(t_dclst *node)
{
	t_token	*tok;

	tok = (t_token *) node->data;
	if (tok->type == TOKEN_PIPE)
		return (1);
	return (0);
}

// Function to check if the token of the node is a tree branch
// (logical operator, pipe or parenthesis)
// Returns 1 if the token is a tree branch, 0 otherwise
int	is_tree_branch(t_dclst *node)
{
	if (!node)
		return (0);
	if (is_logical_operator(node) || is_pipe(node) || is_parenthesis(node))
		return (1);
	return (0);
}
