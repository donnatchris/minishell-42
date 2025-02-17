#include "../../include/minishell.h"
#include "../../include/parser.h"

// Function to print the token in error messages
void	print_token(t_token *token)
{
	if (token->type == TOKEN_PIPE)
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

// Function to print token error messages
void	print_token_error(t_token *token)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	print_token(token);
	ft_printf("\n");
}

// Function to check the syntax of tokens in the doubly circular linked list
int	check_syntax(t_dclst **head)
{
	t_dclst	*current;
	t_token	*token;
	t_token	*next_token;
	t_token	*previous_token;

	if (!head || !*head)
		return (-1);
	current = *head;
	while (1)
	{
		token = (t_token *) current->data;
		next_token = (t_token *) current->next->data;
		previous_token = (t_token *) current->prev->data;
		if (token->priority != 6 && token->priority != 1)
		{
			if ((next_token->priority !=6 && next_token->priority != 1) || (previous_token->priority !=6 && previous_token->priority != 1))
				return (print_token_error(token), -1);
		}
		if (next_token->type == TOKEN_EOF || current->next == *head)
			break ;
		current = current->next;
		token = (t_token *) current->data;
	}
	return (0);
}
