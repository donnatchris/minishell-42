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
	if (token->type >= TOKEN_STRING && token->type <= TOKEN_LITTERAL)
		return (TREE_COMMAND);
	else if (token->type == TOKEN_PIPE)
		return (TREE_PIPE);
	else if (token->type == TOKEN_AND)
		return (TREE_AND);
	else if (token->type == TOKEN_OR)
		return (TREE_OR);
	else if (token->type == TOKEN_REDIR_OUT)
		return (TREE_REDIR_OUT);
	else if (token->type == TOKEN_APPEND)
		return (TREE_APPEND);
	else if (token->type == TOKEN_REDIR_IN)
		return (TREE_REDIR_IN);
	else if (token->type == TOKEN_HEREDOC)
		return (TREE_HEREDOC);
	else if (token->type == TOKEN_SEMICOLON)
		return (TREE_SEMICOLON);
	else if (token->type == TOKEN_PARENTHESIS)
		return (TREE_PARENTHESIS);
	return (TREE_ERROR);
}

// Function to create a new node in the binary tree
// Returns the new node or NULL if an error occurs
t_tree	*create_tree_node(t_dclst *list_node)
{
	t_tree	*tree_node;

	tree_node = (t_tree *) malloc(sizeof(t_tree));
	if (!tree_node)
		return (shell_error_msg("create_tree_node", "malloc failed"), NULL);
	ft_memset(tree_node, 0, sizeof(t_tree));
	tree_node->list_node = list_node;
	tree_node->type = find_tree_node_type((t_token *) list_node->data);
	return (tree_node);
}

// Function to find the priority token in the doubly circular linked list
// Returns the node with the lowest priority or NULL if an error occurs
// THE RETURNED NODE MUST BE FREED AFTER USE
t_dclst	*find_lowest_priority(t_dclst *left, t_dclst *right)
{
	t_dclst	*current;
	t_dclst	*lowest;
	t_token	*token;
	t_token	*lowest_token;
	
	if (!left || !right)
		return (shell_error_msg("find_lowest_priority", "invalid arguments"), NULL);
	current = left;
	lowest = left;
	while (1)
	{
		lowest_token = (t_token *) lowest->data;
		token = (t_token *) current->data;
		if (token->priority < lowest_token->priority && !is_text(current))
			lowest = current;
		else if (is_logical_operator(lowest) && is_logical_operator(current))
			lowest = current;
		if (current == right)
			break ;
		current = current->next;
	}
	return (lowest);
}
//test
// Function to create the binary tree from the doubly circular linked list
// Returns the root of the binary tree or NULL if an error occurs
t_tree	*create_tree(t_dclst *left, t_dclst *right)
{
	t_tree	*tree_node;
	t_dclst	*lowest;

	if (!left || !right)
		return (shell_error_msg("create tree", "invalid arguments"), NULL);
	lowest = find_lowest_priority(left, right);

	// ft_printf("Lowest priority: ");
	// print_a_token((t_token *) lowest->data);

	tree_node = create_tree_node(lowest);
	if (!tree_node)
		return (NULL);
	if (left == right)
		return (tree_node);
	if (lowest != left && !is_text(lowest))
		tree_node->left = create_tree(left, lowest->prev);
	if (lowest != right && !is_redir(lowest) && !is_text(lowest))
		tree_node->right = create_tree(lowest->next, right);
	return (tree_node);
}
