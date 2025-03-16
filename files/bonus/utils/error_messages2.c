/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:27:25 by christophed       #+#    #+#             */
/*   Updated: 2025/03/16 15:35:50 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Function to print the token in error messages
static void	print_token(t_token *token)
{
	if (token->type == TOKEN_PARENTHESIS)
		ft_putstr_fd("`)'", 2);
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

// Function to print error from token parsing
// Returns: -1
int	print_token_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	print_token(token);
	ft_printf("\n");
	return (258);
}

int	print_parenthesis_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd("`)'", 2);
	ft_printf("\n");
	return (258);
}

// Function to print a warning message when the heredoc is not closed
void	warning_msg(char *delimiter, int n_line)
{
	ft_putstr_fd("minishell: warning : here-document at line ", 2);
	ft_putnbr_fd(n_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}
