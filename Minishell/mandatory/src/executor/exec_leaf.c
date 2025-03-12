/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_leaf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:29:06 by christophed       #+#    #+#             */
/*   Updated: 2025/03/12 08:22:59 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to get the next heredoc node
// Returns the next heredoc node, NULL if there is no more heredoc
static t_dclst	*get_next_heredoc(t_dclst *node)
{
	t_dclst	*current;

	current = node;
	while (!is_tree_branch(current) && !is_eof(current))
	{
		if (is_heredoc(current))
			return (current);
		current = current->next;
	}
	return (NULL);
}

// Function to get the next redirection input node
// Returns the next redirection input node
// or NULL if there is no more redirection input
static t_dclst	*get_next_redir_in(t_dclst *node)
{
	t_dclst	*current;

	current = node;
	while (!is_tree_branch(current) && !is_eof(current))
	{
		if (is_redir_in(current))
			return (current);
		current = current->next;
	}
	return (NULL);
}

// Function to get the next redirection output node
// Returns the next redirection output node
// orNULL if there is no more redirection output
static t_dclst	*get_next_redir_out(t_dclst *node)
{
	t_dclst	*current;

	current = node;
	while (!is_tree_branch(current) && !is_eof(current))
	{
		if (is_redir_out(current))
			return (current);
		current = current->next;
	}
	return (NULL);
}

// Function to get the next command node
// Returns the next command node, NULL if there is no more command
static t_dclst	*get_next_cmd(t_dclst *node)
{
	t_dclst	*current;

	current = node;
	while (!is_tree_branch(current) && !is_eof(current))
	{
		if (is_redir(current))
			current = current->next;
		else if (is_text(current))
			return (current);
		current = current->next;
	}
	return (NULL);
}

// Function to execute a leaf node
// (a leaf node is a node that contains a command)
// Returns the status of the command
int	exec_leaf(t_dclst *node, char ***envp, t_general *gen)
{
	t_dclst	*current;
	int		status;

	gen->stdin_backup = dup(STDIN_FILENO);
	if (gen->stdin_backup == -1)
		return (ft_perror("exec_leaf", "dup failed"));
	gen->stdout_backup = dup(STDOUT_FILENO);
	if (gen->stdout_backup == -1)
		return (close(gen->stdin_backup), ft_perror("exec_leaf", "dup failed"));
	current = get_next_heredoc(node);
	if (current)
	{
		status = redir_heredoc(current, envp, gen);
		if (status)
			return (status);
	}
	current = get_next_redir_in(node);
	if (current)
	{
		status = redir_in(current, envp, gen);
		if (status)
			return (status);
	}
	current = get_next_redir_out(node);
	if (current)
		status = redir_out(current, envp, gen);
	current = get_next_cmd(node);
	status = exec_cmd(current, envp, gen);
	end_redir_in(gen->stdin_backup);
	end_redir_out(gen->stdout_backup);
	return (status);
}
