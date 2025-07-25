/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_token_info2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:32:40 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 06:33:28 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Function to check if the token of the node is a text
// (TOKEN_STRING or TOKEN_WORD or TOKEN_LITTERAL)
// Returns 1 if the token is a text, 0 otherwise
int	is_text(t_dclst *node)
{
	t_token	*tok;

	tok = (t_token *) node->data;
	if (tok->type == TOKEN_WORD || tok->type == TOKEN_STRING
		|| tok->type == TOKEN_LITTERAL)
		return (1);
	return (0);
}

// Function to check if the token of the node is a redirection
// (TOKEN_REDIR_IN or TOKEN_REDIR_OUT or TOKEN_APPEND or TOKEN_HEREDOC)
// Returns 1 if the token is a redirection, 0 otherwise
int	is_redir(t_dclst *node)
{
	t_token	*tok;

	tok = (t_token *) node->data;
	if (tok->type == TOKEN_REDIR_IN || tok->type == TOKEN_REDIR_OUT
		|| tok->type == TOKEN_APPEND || tok->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

// Function to check if the token of the node is a heredoc
// (TOKEN_HEREDOC)
// Returns 1 if the token is a heredoc, 0 otherwise
int	is_heredoc(t_dclst *node)
{
	t_token	*tok;

	tok = (t_token *) node->data;
	if (tok->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

// Function to check if the token of the node is a redirection input
// (TOKEN_REDIR_IN)
// Returns 1 if the token is a redirection input, 0 otherwise
int	is_redir_in(t_dclst *node)
{
	t_token	*tok;

	tok = (t_token *) node->data;
	if (tok->type == TOKEN_REDIR_IN)
		return (1);
	return (0);
}

// Function to check if the token of the node is a redirection output
// (TOKEN_REDIR_OUT or TOKEN_APPEND)
// Returns 1 if the token is a redirection output, 0 otherwise
int	is_redir_out(t_dclst *node)
{
	t_token	*tok;

	tok = (t_token *) node->data;
	if (tok->type == TOKEN_REDIR_OUT || tok->type == TOKEN_APPEND)
		return (1);
	return (0);
}
