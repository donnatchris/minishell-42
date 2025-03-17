/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delimiter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:02:53 by christophed       #+#    #+#             */
/*   Updated: 2025/03/16 16:10:24 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to find the delimiters and create an array
// Returns the next heredoc node, NULL if there is no more heredoc
// RETURNS MUST BE FREED AFTER USE
t_delim	*find_delimiter(t_dclst *node)
{
	t_delim	*lim;
	t_dclst	*current;
	char	*temp;

	lim = (t_delim *) malloc(sizeof(t_delim));
	if (!lim)
		return (shell_err_msg("find_delimiter", "malloc failed"), NULL);
	ft_memset(lim, 0, sizeof(t_delim));
	current = node->next;
	lim->str = ft_strdup(((t_token *) current->data)->start);
	if (((t_token *) current->data)->type != TOKEN_WORD)
		lim->is_litteral = 1;
	if (!lim->str)
		return (shell_err_msg("find_delimiter", "ft_strdup failed"), NULL);
	while (!((t_token *) current->data)->space && is_text(current->next))
	{
		if (((t_token *) current->data)->type != TOKEN_WORD
			|| ((t_token *) current->next->data)->type != TOKEN_WORD)
			lim->is_litteral = 1;
		temp = lim->str;
		lim->str = ft_strjoin(temp, ((t_token *) current->next->data)->start);
		free(temp);
		current = current->next;
	}
	return (lim);
}
