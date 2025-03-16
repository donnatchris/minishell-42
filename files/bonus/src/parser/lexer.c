/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:03:51 by christophed       #+#    #+#             */
/*   Updated: 2025/03/15 20:59:34 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to affect the priority to each token
// in the doubly circular linked list
static void	affect_tokens_priority(t_dclst **head)
{
	t_dclst	*current;
	t_token	*tok;

	if (!head || !*head)
		return ;
	current = *head;
	while (1)
	{
		tok = (t_token *) current->data;
		if (tok->type >= TOKEN_STRING && tok->type <= TOKEN_LITTERAL)
			tok->priority = 6;
		else if (tok->type == TOKEN_PIPE)
			tok->priority = 1;
		else if (tok->type == TOKEN_AND || tok->type == TOKEN_OR
			||tok->type == TOKEN_SEMICOLON)
			tok->priority = 0;
		else if (tok->type == TOKEN_PARENTHESIS)
			tok->priority = 2;
		else
			tok->priority = 10;
		current = current->next;
		if (current == *head)
			break ;
	}
}

// Function to fill the data string in the doubly circular linked list
// with the corresponding token type
// Returns the type of the token
static void	null_terminate_token(t_dclst **head)
{
	t_dclst	*current;
	t_token	*token;

	if (!head || !*head)
		return ;
	current = *head;
	while (1)
	{
		token = (t_token *) current->data;
		if (token->type == TOKEN_PARENTHESIS || token->type == TOKEN_STRING
			|| token->type == TOKEN_LITTERAL)
		{
			token->start++;
			token->end--;
			*token->end = '\0';
		}
		else if (token->type == TOKEN_WORD)
			*token->end = '\0';
		token->end = NULL;
		current = current->next;
		if (current == *head)
			break ;
	}
}

// Function to split the input into tokens
// and store them in the doubly circular linked list
// Returns 0 if the function succeeds or -1 if an error occurs
static int	tokenize_to_dclst(char *input, t_dclst **head)
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
		token->str_is_malloc = 0;
		if (ft_strchr(WHITESPACES, *end))
			token->space = 1;
		dclst_add_back(head, token);
	}
	return (0);
}

// Function to create a doubly circular linked list of tokens from the input
// Returns the head of the doubly circular linked list
// or NULL if an error occurs
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
