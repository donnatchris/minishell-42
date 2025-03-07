/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_token_info3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:33:19 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 06:33:23 by christophed      ###   ########.fr       */
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
