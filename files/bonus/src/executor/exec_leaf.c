/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_leaf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nifromon <nifromon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:29:06 by christophed       #+#    #+#             */
/*   Updated: 2025/03/19 22:15:54 by nifromon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to restore STDIN and STDOUT
static void	restore_std(int stdin, int stdout)
{
	close(STDIN_FILENO);
	if (dup2(stdin, STDIN_FILENO) == -1)
		ft_perror("redir_out", "dup2 failed");
	close(stdin);
	close(STDOUT_FILENO);
	if (dup2(stdout, STDOUT_FILENO) == -1)
		ft_perror("redir_out", "dup2 failed");
	close(stdout);
}

// Function to save STDIN and STDOUT
// Returns 0 on success, -1 on error
static int	save_std(t_general *gen)
{
	gen->stdin_backup = dup(STDIN_FILENO);
	if (gen->stdin_backup == -1)
		return (ft_perror("exec_leaf", "dup failed"));
	gen->stdout_backup = dup(STDOUT_FILENO);
	if (gen->stdout_backup == -1)
		return (close(gen->stdin_backup), ft_perror("exec_leaf", "dup failed"));
	return (0);
}

// Function to execute a leaf node
// (a leaf node is a node that contains a command)
// Returns the status of the command
int	exec_leaf(t_dclst *node, t_general *gen)
{
	t_dclst	*current;
	int		status;

	if (save_std(gen) == -1)
		return (-1);
	if (!gen->in_pipe)
		create_heredoc(node, gen);
	status = 0;
	current = get_next_redir(node);
	while (current)
	{
		if (((t_token *) current->data)->type == TOKEN_HEREDOC)
			status += redir_heredoc();
		else if (((t_token *) current->data)->type == TOKEN_REDIR_IN)
			status += redir_in(current, gen);
		else if (is_redir_out(current))
			status += redir_out(current, gen);
		current = get_next_redir(current->next);
	}
	if (status)
		return (1);
	current = get_next_cmd(node);
	status = exec_cmd(current, gen);
	restore_std(gen->stdin_backup, gen->stdout_backup);
	return (status);
}
