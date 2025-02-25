#include "../../include/minishell.h"

// Function to affect the priority to each token in the doubly circular linked list
void	affect_tokens_priority(t_dclst **head)
{
	t_dclst	*current;
	t_token	*tok;

	if (!head || !*head)
		return ;
	current = *head;
	while (1)
	{
		tok = (t_token *) current->data;
		if (tok->type <= TOKEN_AND)
			tok->priority = tok->type;
		else if (tok->type == TOKEN_OR)
			tok->priority = 3;
		else if (tok->type >= TOKEN_REDIR_OUT && tok->type <= TOKEN_HEREDOC)
			tok->priority = 4;
		else if (tok->type == TOKEN_SEMICOLON)
			tok->priority = 5;
		else if (tok->type >= TOKEN_STRING && tok->type <= TOKEN_LITTERAL)
			tok->priority = 6;
		else
			tok->priority = 0;
		current = current->next;
		if (current == *head)
			break ;
	}
}

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
			*(token)->end = '\0';
		}
		else if (token->type == TOKEN_WORD)
			*token->end = '\0';
		else
			token->start = NULL; // was "" before last modification
		token->end = NULL;
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
		token = (t_token *) malloc(sizeof(t_token) + 1);
		if (!token)
			return (-1);
		token->type = type;
		token->start = start;
		token->end = end;
		token->space = 0;
		if (ft_strchr(WHITESPACES, *end))
			token->space = 1;
		dclst_add_back(head, token);
	}
	return (0);
}

// Function to create a doubly circular linked list of tokens from the input
t_dclst	**tokenize(char *input)
{
	t_dclst	**head;

	if (!input)
		return (NULL);
	head = (t_dclst **) malloc(sizeof(t_dclst *));
	if (!head)
		return (NULL);
	ft_memset(head, 0, sizeof(t_dclst **));
	if (tokenize_to_dclst(input, head) == -1)
		return (dclst_clear(head), NULL);
	affect_tokens_priority(head);
	null_terminate_token(head);
	return (head);
}
