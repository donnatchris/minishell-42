#include "../../include/minishell.h"
#include "../../include/parser.h"

// Function to fill the data string in the doubly circular linked list
void	null_terminate_token(t_dclst **head)
{
	t_dclst	*current;
	t_token	*token;

	if (!head || !*head)
		return ;
	current = *head;
	while (1)
	{
		token = (t_token *) current->data;
		if (token->type == TOKEN_PARENTHESIS || token->type == TOKEN_STRING || token->type == TOKEN_LITTERAL)
		{
			token->start++;
			token->end--;
			*token->end = '\0';
		}
		else if (token->type == TOKEN_WORD)
			*token->end = '\0';
		else
				token->start = NULL;
		token->end = NULL;
		current = current->next;
		if (current == *head)
			break ;
	}
}

// Function to clear only the data from the doubly circular linked list
void	clear_dclst_data(t_dclst **head)
{
	t_dclst	*current;

	if (!head || !*head)
		return ;
	current = *head;
	while (1)
	{
		if (current->data)
			free(current->data);
		current->data = NULL;
		current = current->next;
		if (current == *head)
			break ;
	}
}

// Function to split the input into tokens and store them in the doubly circular linked list
int	tokenize_to_dclst(char *input, t_dclst **head)
{
	t_token	*token;
	char	*string;
	char	*start;
	char	*end;
	int		type;

	string = input;
	type = NOTHING;
	while (type != TOKEN_EOF)
	{
		type = get_token(&string, input + ft_strlen(input), &start, &end);
		if (type == TOKEN_ERROR)
			return (-1);
		token = (t_token *) malloc(sizeof(t_token));
		if (!token)
			return (-1);
		token->type = type;
		token->start = start;
		token->end = end;
		token->priority = token->type;
		if (token->priority > 10)
			token->priority = 10;
		dclst_add_back(head, token);
	}
	return (0);
}

// Function to create a doubly circular linked list of tokens from the input
t_dclst	**tokenize(char *input)
{
	t_dclst	**head;

	head = NULL;
	head = malloc(sizeof(t_dclst *));
	if (!head)
		return (NULL);
	if (tokenize_to_dclst(input, head) == -1)
	{
		clear_dclst_data(head);
		dclst_clear(head);
		return (NULL);
		// atention input à free dans la fonction appelante si retourne NULL
		// et que input a été allouée dynamiquement (comme avec readline())
	}
	null_terminate_token(head);
	return (head);
}
