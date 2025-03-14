/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_token_info3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:33:19 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 11:59:33 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Function to check if the token of the node has a space
// Returns 1 if the token has a space, 0 otherwise
int	has_space(t_dclst *node)
{
	t_token	*tok;

	tok = (t_token *) node->data;
	if (tok->space)
		return (1);
	return (0);
}

// Function to check if the token of the node is part of a redirection filename
// Returns 1 if it's a filename, 0 otherwise
int	is_filename(t_dclst *node)
{
	while (is_text(node) && !has_space(node->prev) && is_text(node->prev))
		node = node->prev;
	if (is_redir(node->prev))
		return (1);
	return (0);
}
