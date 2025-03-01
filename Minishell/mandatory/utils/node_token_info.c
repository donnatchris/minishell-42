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

// Function to check if the token of the node is a text
// (TOKEN_STRING or TOKEN_WORD or TOKEN_LITTERAL)
// Returns 1 if the token is a text, 0 otherwise
int	is_text(t_dclst *node)
{
	t_token	*tok;

	tok = (t_token *) node->data;
	if (tok->type == TOKEN_WORD || tok->type == TOKEN_STRING || tok->type == TOKEN_LITTERAL)
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
	if (tok->type == TOKEN_REDIR_IN || tok->type == TOKEN_REDIR_OUT || tok->type == TOKEN_APPEND || tok->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

// Function to check if the token of the node is a logical operator
// (TOKEN_AND or TOKEN_OR or TOKEN_SEMICOLON)
// Returns 1 if the token is a logical operator, 0 otherwise
int	is_logical_operator(t_dclst *node)
{
	t_token	*tok;

	tok = (t_token *) node->data;
	if (tok->type == TOKEN_AND || tok->type == TOKEN_OR || tok->type == TOKEN_SEMICOLON)
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
int is_eof(t_dclst *node)
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
