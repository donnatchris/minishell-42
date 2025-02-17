#include "../../include/minishell.h"
#include "../../include/parser.h"

// Function to print the tree
void	print_tree(t_tree *root)
{
	if (!root)
		return ;
	if (root->left)
		print_tree(root->left);
	if (root->right)
		print_tree(root->right);
	ft_printf("token: %s\n", root->token->start);
}

// Function to free the binary tree
void	clear_tree(t_tree *root)
{
	if (!root)
		return ;
	if (root->left)
		clear_tree(root->left);
	if (root->right)
		clear_tree(root->right);
	free(root);
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
t_tree	*create_tree(t_dclst *first, t_dclst *last)
{
	t_tree	*node;
	t_dclst	*lowest;

	if (!first || !last)
		return (NULL);
	lowest = find_lowest_priority(first, last);
	node = create_tree_node((t_token *) lowest->data);
	if (!node)
		return (NULL);
	if (first == last)
		return (node);
	if (lowest != first)
		node->left = create_tree(first, lowest->prev);
	if (lowest != last)
		node->right = create_tree(lowest->next, last);
	return (node);
}
