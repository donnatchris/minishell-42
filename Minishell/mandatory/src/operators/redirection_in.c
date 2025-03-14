/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:36:16 by christophed       #+#    #+#             */
/*   Updated: 2025/03/14 11:24:47 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to close redir_out
// Returns exec_tree on success, -1 on error
void	end_redir_in(int stdin_backup)
{
	close(STDIN_FILENO);
	if (dup2(stdin_backup, STDIN_FILENO) == -1)
		ft_perror("redir_out", "dup2 failed");
	close(stdin_backup);
}

// Function to handle a redirection_in '<' from a node
// Returns 0 on success, -1 on error
static int	redir_in_from_node(t_dclst *node, t_general *gen)
{
	t_token	*token;
	char	*filename;
	int		fd;

	token = (t_token *) node->next->data;
	if (!token || token->priority != 6 || !token->start)
		return (shell_err_msg("redir_in", "invalid arguments"));
	filename = extract_filename(node->next, gen);
	if (!filename)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (open_error(filename));
	free(filename);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), ft_perror("redir_in", "dup2 failed"));
	close(fd);
	return (0);
}

// Function to handle multiple redirection_in '<'
// Returns 0 on success, -1 on error
int	redir_in(t_dclst *node, t_general *gen)
{
	if (!node || !gen)
		return (shell_err_msg("redir_in", "invalid arguments"));
	return (redir_in_from_node(node, gen));
}
