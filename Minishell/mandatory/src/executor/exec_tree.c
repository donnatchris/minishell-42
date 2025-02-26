#include "../../include/minishell.h"

// Function to exec the tree recursively
// Returns 0 if the command was executed successfully
// Returns -1 if an error occurred
// Returns the status of the command if it is a logical operator
int	exec_tree(t_tree *tree_node, char ***envp, t_general *gen)
{
    int status;
	
	status = 0;
    if (!tree_node)
        return (0);
    if (tree_node->type == TREE_COMMAND)
        return exec_node(tree_node->list_node, envp, gen);
    if (tree_node->type == TREE_PIPE)
        return (pipe_operator(tree_node->left->list_node, tree_node->right->list_node, envp, gen));
    if (tree_node->type == TREE_AND)
    {
        status = exec_tree(tree_node->left, envp, gen);
        if (status == 0)
            status = exec_tree(tree_node->right, envp, gen);
        return (status);
    }
    if (tree_node->type == TREE_OR)
    {
        status = exec_tree(tree_node->left, envp, gen);
        if (status != 0)
            status = exec_tree(tree_node->right, envp, gen);
        return (status);
    }
    if (tree_node->type == TREE_SEMICOLON)
        return (exec_tree(tree_node->right, envp, gen));
    if (tree_node->type == TREE_REDIR_OUT || tree_node->type == TREE_APPEND)
		return (redir_out(tree_node, envp, gen));
    if (tree_node->type == TREE_REDIR_IN)
		return (0);
		// return redir_in(tree_node, envp, gen);
    if (tree_node->type == TREE_HEREDOC)
		return (0);
		// return heredoc(tree_node, envp, gen);
    return (-1);
// 	Gestion des redirections
// Actuellement, tu appelles redir_out(), redir_in(), heredoc(), mais sans vérifier si l’enfant gauche contient bien une commande.
// Il faudra rediriger les STDIN ou STDOUT et ensuite exécuter la commande.
}
