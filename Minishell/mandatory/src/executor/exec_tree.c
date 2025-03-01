#include "../../include/minishell.h"

// Function to exec the control operators of the tree ('&&', '||', ';')
// Returns the exit_status of the command
int	exec_control_operator(t_tree *tree, char ***envp, t_general *gen)
{
	if (tree->type == TREE_AND)
	{
		gen->exit_status = exec_tree(tree->left, envp, gen);
		if (gen->exit_status == 0)
		gen->exit_status = exec_tree(tree->right, envp, gen);
	}
	else if (tree->type == TREE_OR)
	{
		gen->exit_status = exec_tree(tree->left, envp, gen);
		if (gen->exit_status != 0)
		gen->exit_status = exec_tree(tree->right, envp, gen);
	}
	else if (tree->type == TREE_SEMICOLON)
	{
		if (tree->left)
			gen->exit_status = exec_tree(tree->left, envp, gen);
		if (tree->right)
			gen->exit_status = exec_tree(tree->right, envp, gen);
	}
	else
		gen->exit_status = -1;
	return (gen->exit_status);
}

// Function to exec the tree recursively
// Returns 0 if the command was executed successfully
// Returns -1 if an error occurred
// Returns the exit_status of the command if it is a logical operator
int	exec_tree(t_tree *tree, char ***envp, t_general *gen)
{
    if (!tree)
        return (0);
	if (tree->type == TREE_COMMAND)
		gen->exit_status = exec_node(tree->list_node, envp, gen);
	else if (tree->type == TREE_PIPE)
		gen->exit_status = pipe_operator(tree, envp, gen);
	else if (tree->type == TREE_REDIR_OUT || tree->type == TREE_APPEND)
		gen->exit_status = redir_out(tree, envp, gen);
	else if (tree->type == TREE_REDIR_IN)
		gen->exit_status = redir_in(tree, envp, gen);
	else if (tree->type == TREE_HEREDOC)
		gen->exit_status = redir_heredoc(tree, envp, gen);
	else if (tree->type == TREE_PARENTHESIS)
	{
		gen->exit_status = run_parenthesis(tree, envp, gen);
		if (tree->left)
			gen->exit_status = exec_tree(tree->left, envp, gen);
		if (tree->right)
			gen->exit_status = exec_tree(tree->right, envp, gen);
	}
	else
		gen->exit_status = exec_control_operator(tree, envp, gen);
    return (gen->exit_status);
}
