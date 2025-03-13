/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:20:12 by chdonnat          #+#    #+#             */
/*   Updated: 2025/03/13 12:21:54 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Function to get the next heredoc node
// Returns the next heredoc node, NULL if there is no more heredoc
// or NULL if there is no more redirection input
t_dclst	*get_next_heredoc(t_dclst *node)
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

// Function to get the next command node
// Returns the next command node, NULL if there is no more command
// or NULL if there is no more redirection input
t_dclst	*get_next_cmd(t_dclst *node)
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

// Function to get the next redirection input node
// Returns the next redirection input node
// or NULL if there is no more redirection input
t_dclst	*get_next_redir(t_dclst *node)
{
	t_dclst	*current;

	current = node;
	while (!is_tree_branch(current) && !is_eof(current))
	{
		if (is_redir(current))
			return (current);
		current = current->next;
	}
	return (NULL);
}
