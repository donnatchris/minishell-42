#include "../../include/minishell.h"
#include "../../include/parser.h"

// Function to free the binary tree
void	free_tree(t_tree **root)
{
	if (!root || !*root)
		return ;
	if ((*root)->left)
		free_tree(&(*root)->left);
	if ((*root)->right)
		free_tree(&(*root)->right);
	free(*root);
	*root = NULL;
}

// Function to create a new node in the binary tree
t_tree	*create_tree_node(t_token *token)
{
	t_tree	*node;

	node = (t_tree *) malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_tree));
	node->token = token;
	return (node);
}

// Function to find the priority token in the doubly circular linked list
t_dclst	*find_lowest_priority(t_dclst *first_node, t_dclst *last_node)
{
	t_dclst	*current;
	t_dclst	*lowest;
	t_token	*token;
	t_token	*lowest_token;

	if (!first_node || !last_node)
		return (NULL);
	current = last_node;
	lowest = last_node;
	while (1)
	{
		lowest_token = (t_token *) lowest->data;
		token = (t_token *) current->data;
		if (token->priority < lowest_token->priority)
			lowest = current;
		if (current == first_node)
			break ;
		current = current->prev;
	}
	return (lowest);
}

// Function to create the binary tree from the doubly circular linked list
t_tree	*create_tree(t_dclst *first_node, t_dclst *last_node)
{
	t_tree	*node;
	t_dclst	*lowest;

	if (!first_node || !last_node)
		return (NULL);
	lowest = find_lowest_priority(first_node, last_node);
	node = create_tree_node((t_token *) lowest->data);
	if (!node)
		return (NULL);
	if (first_node == last_node)
		return (node);
	node->left = create_tree(first_node, lowest->prev);
	node->right = create_tree(lowest->next, last_node);
	return (node);
}
