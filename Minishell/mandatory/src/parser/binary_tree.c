#include "../../include/minishell.h"
#include "../../include/parser.h"

// Function to create a new node in the binary tree
t_tree	*create_tree_node(t_token *token)
{
	t_tree	*node;

	node = (t_tree *) malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->cmd = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

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
	t_token	*token;
	t_dclst	*lowest;

	if (!first_node || !last_node)
		return (NULL);
	node = (t_tree *) malloc(sizeof(t_tree *));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_tree));
	lowest = find_lowest_priority(first_node, last_node);
	token = (t_token *) lowest->data;
	node->token = token;
	node->left = NULL;
	node->right = NULL;
}
