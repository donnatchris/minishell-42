/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:29:56 by christophed       #+#    #+#             */
/*   Updated: 2025/03/12 10:36:12 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to execute a logical operator
// Returns the status of the command
static int	exec_logical_operator(t_tree *tree, t_general *gen)
{
	if (tree->type == TREE_AND)
	{
		gen->exit_status = exec_tree(tree->left, gen);
		if (gen->exit_status == 0)
			gen->exit_status = exec_tree(tree->right, gen);
	}
	else if (tree->type == TREE_OR)
	{
		gen->exit_status = exec_tree(tree->left, gen);
		if (gen->exit_status != 0)
			gen->exit_status = exec_tree(tree->right, gen);
	}
	else if (tree->type == TREE_SEMICOLON)
	{
		if (tree->left)
			gen->exit_status = exec_tree(tree->left, gen);
		if (tree->right)
			gen->exit_status = exec_tree(tree->right, gen);
	}
	else
		gen->exit_status = shell_err_msg("exec_tree",
				"invalid tree node type");
	return (gen->exit_status);
}

// Function to exec the tree recursively
// Returns 0 if the command was executed successfully
// Returns -1 if an error occurred
// Returns the status of the command if it is a logical operator
int	exec_tree(t_tree *tree_node, t_general *gen)
{
	if (!tree_node)
		return (0);
	else if (tree_node->type == TREE_COMMAND)
		gen->exit_status = exec_leaf(tree_node->list_node, gen);
	else if (tree_node->type == TREE_PARENTHESIS)
		gen->exit_status = run_parenthesis(tree_node, gen);
	else if (tree_node->type == TREE_PIPE)
		gen->exit_status = pipe_operator(tree_node, gen);
	else
		gen->exit_status = exec_logical_operator(tree_node, gen);
	return (gen->exit_status);
}
