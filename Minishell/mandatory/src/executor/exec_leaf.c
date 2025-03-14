/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_leaf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:29:06 by christophed       #+#    #+#             */
/*   Updated: 2025/03/14 11:20:19 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to restore STDIN and STDOUT
static void	restore_std(int stdin, int stdout)
{
	end_redir_in(stdin);
	end_redir_out(stdout);
}

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
		{
			if (redir_in(current, gen))
				return (restore_std(gen->stdin_backup, gen->stdout_backup), 1);
		}
		else if (((t_token *) current->data)->type == TOKEN_REDIR_OUT)
		{
			if (redir_out(current, gen))
				return (restore_std(gen->stdin_backup, gen->stdout_backup), 1);
		}
		current = get_next_redir(current->next);
	}
	current = get_next_cmd(node);
	status = exec_cmd(current, gen);
	restore_std(gen->stdin_backup, gen->stdout_backup);
	return (status);
}
