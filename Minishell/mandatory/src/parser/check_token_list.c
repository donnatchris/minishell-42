#include "../../include/minishell.h"

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

// Function to check the syntax of tokens in the doubly circular linked list
// Returns 0 if the syntax is correct, -1 otherwise
int	check_syntax(t_dclst **head)
{
	t_dclst	*current;
	t_token	*token;
	t_token	*next_tok;
	t_token	*prev_tok;

	if (!head || !*head)
		return (-1);
		current = *head;
	if (dclst_count_nodes(*head) < 2 || ((t_token *)current->data)->priority != 6)
		return (print_token_error((t_token *)current->data));
	while (1)
	{
		token = (t_token *) current->data;
		next_tok = (t_token *) current->next->data;
		prev_tok = (t_token *) current->prev->data;
		if (token->priority != 6 && token->priority != 1)
		{
			if ((next_tok->priority !=6 && next_tok->priority != 1) || (prev_tok->priority !=6 && prev_tok->priority != 1))
				return (print_token_error(token));	//next_tok?
		}
		if (next_tok->type == TOKEN_EOF || current->next == *head)
			break ;
		current = current->next;
		token = (t_token *) current->data;
	}
	return (0);
}
