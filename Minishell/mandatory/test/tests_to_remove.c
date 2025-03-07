/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_to_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:00:16 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 06:45:35 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Function to print the tree
void	print_tree(t_tree *root)
{
	if (!root)
		return ;
	if (root->left)
		print_tree(root->left);
	if (root->right)
		print_tree(root->right);
	print_a_token((t_token *) root->list_node->data);
}

// Function to print a string from one pointer to another
void	print_string(char *start, char *end)
{
	while (start != end)
	{
		ft_printf("%c", *start);
		start++;
	}
	ft_printf("\n");
}

// Function to print a token
void	print_other_tokens(t_token *token)
{
	if (token->type == TOKEN_HEREDOC)
		ft_printf("TOKEN_HEREDOC: ");
	else if (token->type == TOKEN_APPEND)
		ft_printf("TOKEN_APPEND: ");
	else if (token->type == TOKEN_AND)
		ft_printf("TOKEN_AND: ");
	else if (token->type == TOKEN_OR)
		ft_printf("TOKEN_OR: ");
	else if (token->type == TOKEN_SEMICOLON)
		ft_printf("TOKEN_SEMICOLON: ");
	else if (token->type == TOKEN_STRING)
		ft_printf("TOKEN_STRING: ");
	else if (token->type == TOKEN_LITTERAL)
		ft_printf("TOKEN_LITTERAL: ");
	else if (token->type == TOKEN_PARENTHESIS)
		ft_printf("TOKEN_PARENTHESIS: ");
	else if (token->type == TOKEN_EOF)
		ft_printf("TOKEN_EOF: ");
	else if (token->type == TOKEN_ERROR)
		ft_printf("TOKEN_ERROR: ");
}

// Function to print a token
void	print_a_token(t_token *token)
{
	if (!token)
	{
		ft_printf("No tokens to print\n");
		return ;
	}
	if (token->type == TOKEN_WORD)
		ft_printf("TOKEN_WORD: ");
	else if (token->type == TOKEN_PIPE)
		ft_printf("TOKEN_PIPE: ");
	else if (token->type == TOKEN_REDIR_IN)
		ft_printf("TOKEN_REDIR_IN: ");
	else if (token->type == TOKEN_REDIR_OUT)
		ft_printf("TOKEN_REDIR_OUT: ");
	else
		print_other_tokens(token);
	print_string(token->start, token->end);
	ft_printf("%s\n", token->start);
	if (token->space)
		ft_printf("\thas space\n");
	if (!token->space)
		ft_printf("\tno space\n");
}

// Function to print the doubly circular linked list of tokens
void	print_dclst_tokens(t_dclst **head)
{
	t_dclst	*current;
	t_token	*token;

	if (!head || !*head)
	{
		ft_printf("No list to print\n");
		return ;
	}
	current = *head;
	while (1)
	{
		token = (t_token *) current->data;
		print_a_token(token);
		current = current->next;
		if (current == *head)
			break ;
	}
}
