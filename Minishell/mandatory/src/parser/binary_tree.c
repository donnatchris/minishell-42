#include "../../include/minishell.h"

// Function to print the tree
void	print_tree(t_tree *root)
{
	// Function to remove before submitting
	if (!root)
		return ;
	if (root->left)
		print_tree(root->left);
	if (root->right)
		print_tree(root->right);
	print_a_token((t_token *) root->list_node->data);
}

// Function to find the type of the tree node
// Returns the type of the tree node
int	find_tree_node_type(t_token *token)
{
	if (token->type > NOTHING && token->type < TOKEN_STRING)
		return (token->type);
	if (token->type >= TOKEN_STRING && token->type <= TOKEN_LITTERAL)
		return (TREE_COMMAND);
	return (TREE_ERROR);
}

// Function to create a new node in the binary tree
// Returns the new node or NULL if an error occurs
t_tree	*create_tree_node(t_dclst *list_node)
{
	t_tree	*tree_node;

	tree_node = (t_tree *) malloc(sizeof(t_tree));
	if (!tree_node)
		return (NULL);
	ft_memset(tree_node, 0, sizeof(t_tree));
	tree_node->list_node = list_node;
	tree_node->type = find_tree_node_type((t_token *) list_node->data);
	return (tree_node);
}

// Function to find the priority token in the doubly circular linked list
// Returns the node with the lowest priority or NULL if an error occurs
// THE RETURNED NODE MUST BE FREED AFTER USE
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
// Returns the root of the binary tree or NULL if an error occurs
t_tree	*create_tree(t_dclst *first, t_dclst *last)
{
	t_tree	*tree_node;
	t_dclst	*lowest;

	if (!first || !last)
		return (NULL);
	lowest = find_lowest_priority(first, last);
	
	ft_printf("Lowest priority: ");
	print_a_token((t_token *) lowest->data);

	tree_node = create_tree_node(lowest);
	if (!tree_node)
		return (NULL);
	if (first == last)
		return (tree_node);
	if (lowest != first)
		tree_node->left = create_tree(first, lowest->prev);
	if (lowest != last)
		tree_node->right = create_tree(lowest->next, last);
	return (tree_node);
}
