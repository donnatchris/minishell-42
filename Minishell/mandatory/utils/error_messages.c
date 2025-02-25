#include "../include/minishell.h"

// Function to print error from token parsing
int	print_token_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	print_token(token);
	ft_printf("\n");
	return (-1);
}

// Function to print the token in error messages
void	print_token(t_token *token)
{
	if (token->type == TOKEN_PARENTHESIS)
		ft_putstr_fd("`()'", 2);
	else if (token->type == TOKEN_PIPE)
		ft_putstr_fd("`|'", 2);
	else if (token->type == TOKEN_AND)
		ft_putstr_fd("`&&'", 2);
	else if (token->type == TOKEN_OR)
		ft_putstr_fd("`||'", 2);
	else if (token->type == TOKEN_SEMICOLON)
		ft_putstr_fd("`;'", 2);
	else if (token->type == TOKEN_REDIR_OUT)
		ft_putstr_fd("`>'", 2);
	else if (token->type == TOKEN_APPEND)
		ft_putstr_fd("`>>'", 2);
	else if (token->type == TOKEN_REDIR_IN)
		ft_putstr_fd("`<'", 2);
	else if (token->type == TOKEN_HEREDOC)
		ft_putstr_fd("`<<'", 2);
	else if (token->type == TOKEN_EOF)
		ft_putstr_fd("`newline'", 2);
	else
		ft_putstr_fd(token->start, 2);
}

// Function to print perror message with "minishell: " prefix
int	ft_perror(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	perror(msg);
	return (-1);
}

// Function to print an error message when execve_cmd fails
// Returns: -1
int	shell_error_msg(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

// Function to print error message of export_cmd
int	shell_error_quote(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (-1);
}
