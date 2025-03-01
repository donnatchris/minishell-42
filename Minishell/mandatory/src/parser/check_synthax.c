#include "../../include/minishell.h"


int	check_operator(t_dclst *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	if (!is_text(node->prev) && !is_parenthesis(node->prev))
		return (print_token_error(token));
	if (!is_text(node->next) && !is_parenthesis(node->next))
		return (print_token_error(token));
	return (0);
}

// Function to check the syntax of tokens in the doubly circular linked list
// Returns 0 if the syntax is correct, -1 otherwise
int	check_syntax(t_dclst **head)
{
	t_dclst	*current;

	if (!head || !*head)
		return (-1);
	current = *head;
	while (1)
	{
		if (is_logical_operator(current) || is_pipe(current))
			if (check_operator(current) == -1)
				return (-1);
		if (is_redir(current))
		{
			if (!is_text(current->next))
				return (print_token_error((t_token *) current->data));
		}
		if (is_parenthesis(current))
		{
			if (is_parenthesis(current->next))
				return (print_token_error((t_token *) current->data));
		}
		current = current->next;
		if (is_eof(current) || current->next == *head)
			break ;
	}
	return (0);
}
