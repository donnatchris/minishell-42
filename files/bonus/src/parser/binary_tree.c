/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:00:25 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 05:24:20 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to find the type of the tree node
// Returns the type of the tree node
static int	find_tree_node_type(t_token *token)
{
	if (token->type == TOKEN_PIPE)
		return (TREE_PIPE);
	else if (token->type == TOKEN_AND)
		return (TREE_AND);
	else if (token->type == TOKEN_OR)
		return (TREE_OR);
	else if (token->type == TOKEN_SEMICOLON)
		return (TREE_SEMICOLON);
	else if (token->type == TOKEN_PARENTHESIS)
		return (TREE_PARENTHESIS);
	else
		return (TREE_COMMAND);
}

// Function to create a new node in the binary tree
// Returns the new node or NULL if an error occurs
static t_tree	*create_tree_node(t_dclst *list_node)
{
	t_tree	*tree_node;

	tree_node = (t_tree *) malloc(sizeof(t_tree));
	if (!tree_node)
		return (shell_err_msg("create_tree_node", "malloc failed"), NULL);
	ft_memset(tree_node, 0, sizeof(t_tree));
	tree_node->list_node = list_node;
	tree_node->type = find_tree_node_type((t_token *) list_node->data);
	return (tree_node);
}

// Function to find the priority token in the doubly circular linked list
// Returns the node with the lowest priority or NULL if an error occurs
// THE RETURNED NODE MUST BE FREED AFTER USE
static t_dclst	*find_lowest_priority(t_dclst *left, t_dclst *right)
{
	t_dclst	*current;
	t_dclst	*lowest;
	t_token	*token;
	t_token	*lowest_token;

	if (!left || !right)
		return (shell_err_msg("find_lowest_priority",
				"invalid arguments"), NULL);
	current = right;
	lowest = left;
	while (1)
	{
		lowest_token = (t_token *) lowest->data;
		token = (t_token *) current->data;
		if (is_tree_branch(current) && token->priority < lowest_token->priority)
			lowest = current;
		if (current == left)
			break ;
		current = current->prev;
	}
	return (lowest);
}

// Function to create the binary tree from the doubly circular linked list
// Returns the root of the binary tree or NULL if an error occurs
t_tree	*create_tree(t_dclst *left, t_dclst *right)
{
	t_tree	*tree_node;
	t_dclst	*lowest;

	if (!left || !right)
		return (shell_err_msg("create tree", "invalid arguments"), NULL);
	lowest = find_lowest_priority(left, right);
	tree_node = create_tree_node(lowest);
	if (!tree_node)
		return (NULL);
	if (is_tree_branch(lowest))
	{
		if (lowest != left)
			tree_node->left = create_tree(left, lowest->prev);
		if (lowest != right)
			tree_node->right = create_tree(lowest->next, right);
	}
	return (tree_node);
}
