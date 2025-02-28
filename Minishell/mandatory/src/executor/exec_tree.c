#include "../../include/minishell.h"

// Function to exec the tree recursively
// Returns 0 if the command was executed successfully
// Returns -1 if an error occurred
// Returns the exit_status of the command if it is a logical operator
int	exec_tree(t_tree *tree_node, char ***envp, t_general *gen)
{
    if (!tree_node)
        return (0);
    if (tree_node->type == TREE_PARENTHESIS)
	{
		gen->exit_status = run_parenthesis(tree_node, envp, gen);
		if (tree_node->left)
			gen->exit_status = exec_tree(tree_node->left, envp, gen);
		if (tree_node->right)
			gen->exit_status = exec_tree(tree_node->right, envp, gen);
	}
	else if (tree_node->type == TREE_COMMAND)
		gen->exit_status = exec_node(tree_node->list_node, envp, gen);
	else if (tree_node->type == TREE_PIPE)
		gen->exit_status = pipe_operator(tree_node, envp, gen);
    else if (tree_node->type == TREE_AND)
    {
        gen->exit_status = exec_tree(tree_node->left, envp, gen);
        if (gen->exit_status == 0)
            gen->exit_status = exec_tree(tree_node->right, envp, gen);
    }
    else if (tree_node->type == TREE_OR)
    {
        gen->exit_status = exec_tree(tree_node->left, envp, gen);
        if (gen->exit_status != 0)
            gen->exit_status = exec_tree(tree_node->right, envp, gen);
    }
    else if (tree_node->type == TREE_SEMICOLON)
	{
		if (tree_node->left)
			gen->exit_status = exec_tree(tree_node->left, envp, gen);
		if (tree_node->right)
			gen->exit_status = exec_tree(tree_node->right, envp, gen);
	}
    else if (tree_node->type == TREE_REDIR_OUT)
		gen->exit_status = redir_out(tree_node, envp, gen, O_TRUNC);
	else if (tree_node->type == TREE_APPEND)
		gen->exit_status = redir_out(tree_node, envp, gen, O_APPEND);
    else if (tree_node->type == TREE_REDIR_IN)
		gen->exit_status = redir_in(tree_node, envp, gen);
	else if (tree_node->type == TREE_HEREDOC)
		gen->exit_status = redir_heredoc(tree_node, envp, gen);
    else if (tree_node->type == TREE_HEREDOC)
		gen->exit_status = redir_heredoc(tree_node, envp, gen);
    return (gen->exit_status);
// 	Gestion des redirections
// Actuellement, tu appelles redir_out(), redir_in(), heredoc(), mais sans vérifier si l’enfant gauche contient bien une commande.
// Il faudra rediriger les STDIN ou STDOUT et ensuite exécuter la commande.
}
