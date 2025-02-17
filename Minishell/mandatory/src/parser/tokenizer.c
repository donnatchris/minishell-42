#include "../../include/minishell.h"
#include "../../include/parser.h"

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
		{
			if (((t_token *) current->data)->str)
				free(((t_token *) current->data)->str);
			free(current->data);
		}
		current->data = NULL;
		current = current->next;
		if (current == *head)
			break ;
	}
}

// Function to split the input into tokens and store them in the doubly circular linked list
int	tokenize(char *input, t_dclst **head)
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
		token->priority = type;
		if (token->priority > 10)
			token->priority = 10;
		dclst_add_back(head, token);
	}
	return (0);
}

// Function to create a doubly circular linked list of tokens from the input
t_dclst	**tokenize_to_dclst(char *input)
{
	t_dclst	**head;

	head = NULL;
	head = malloc(sizeof(t_dclst *));
	if (!head)
		return (NULL);
	if (tokenize(input, head) == -1)
	{
		clear_dclst_data(head);
		dclst_clear(head);
		return (NULL);
		// atention input à free dans la fonction appelante si retourne NULL
		// et que input a été allouée dynamiquement (comme avec readline())
	}
	return (head);
}
