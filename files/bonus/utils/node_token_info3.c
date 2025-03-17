/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_token_info3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:33:19 by christophed       #+#    #+#             */
/*   Updated: 2025/03/15 21:49:30 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Function to check if the token of the node has a space
// Returns 1 if the token has a space, 0 otherwise
int	has_space(t_dclst *node)
{
	t_token	*tok;

	tok = (t_token *) node->data;
	if (tok->space)
		return (1);
	return (0);
}

// Function to check if the token of the node is part of a redirection filename
// Returns 1 if it's a filename, 0 otherwise
int	is_filename(t_dclst *node)
{
	while (is_text(node) && !has_space(node->prev) && is_text(node->prev))
		node = node->prev;
	if (is_redir(node->prev))
		return (1);
	return (0);
}

// Function to check if the token of the node is a and or or operator
// (TOKEN_AND or TOKEN_OR)
// Returns 1 if the token is a and or or operator, 0 otherwise
int	is_and_or(t_dclst *node)
{
	t_token	*tok;

	tok = (t_token *) node->data;
	if (tok->type == TOKEN_AND || tok->type == TOKEN_OR)
		return (1);
	return (0);
}

// Function to check if the token of the node is a semicolon
// (TOKEN_SEMICOLON)
// Returns 1 if the token is a semicolon, 0 otherwise
int	is_semicolon(t_dclst *node)
{
	t_token	*tok;

	tok = (t_token *) node->data;
	if (tok->type == TOKEN_SEMICOLON)
		return (1);
	return (0);
}
