/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_leaf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:29:06 by christophed       #+#    #+#             */
/*   Updated: 2025/03/13 18:36:25 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to execute a leaf node
// (a leaf node is a node that contains a command)
// Returns the status of the command
int	exec_leaf(t_dclst *node, t_general *gen)
{
	t_dclst	*current;
	int		status;

	gen->stdin_backup = dup(STDIN_FILENO);
	if (gen->stdin_backup == -1)
		return (ft_perror("exec_leaf", "dup failed"));
	gen->stdout_backup = dup(STDOUT_FILENO);
	if (gen->stdout_backup == -1)
		return (close(gen->stdin_backup), ft_perror("exec_leaf", "dup failed"));
	if (!gen->in_pipe)
		create_heredoc(node, gen);
	current = get_next_redir(node);
	while (current)
	{
		if (((t_token *) current->data)->type == TOKEN_HEREDOC)
			redir_heredoc();
		else if (((t_token *) current->data)->type == TOKEN_REDIR_IN)
			redir_in(current, gen);
		else if (((t_token *) current->data)->type == TOKEN_REDIR_OUT)
			redir_out(current, gen);
		current = get_next_redir(current->next);
	}
	current = get_next_cmd(node);
	status = exec_cmd(current, gen);
	end_redir_in(gen->stdin_backup);
	end_redir_out(gen->stdout_backup);
	return (status);
}
