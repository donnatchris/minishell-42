/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:50:32 by christophed       #+#    #+#             */
/*   Updated: 2025/03/14 11:48:22 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to find the redirection flag
// Returns O_TRUNC if the redirection is '>',
// O_APPEND if the redirection is '>>'
int	redir_flag(t_dclst *node)
{
	if (((t_token *) node->data)->type == TOKEN_REDIR_OUT)
		return (O_TRUNC);
	else
		return (O_APPEND);
}

// Function to get the next redirection node
// Returns the next redirection node, NULL if there is no more redirection
t_dclst	*next_redir_out(t_dclst *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	while (1)
	{
		node = node->next;
		token = (t_token *) node->data;
		if (token->type == TOKEN_REDIR_OUT || token->type == TOKEN_APPEND)
			return (node);
		if (!is_text(node))
			break ;
	}
	return (NULL);
}

// Function to handle one redirection '>' or '>>'
// Returns 0 on success, -1 on error
int	redir_out_from_node(t_dclst *node, t_general *gen, int flag)
{
	t_token	*token;
	char	*filename;
	int		fd;

	token = (t_token *) node->next->data;
	if (!token || token->priority != 6 || !token->start)
		return (shell_err_msg("redir_from_node", "invalid arguments"));
	filename = extract_filename(node->next, gen);
	if (!filename)
		return (1);
	fd = open(filename, O_CREAT | O_WRONLY | flag, 0644);
	if (fd == -1)
		return (open_error(filename));
	free(filename);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), ft_perror("redir_out", "dup2 failed"));
	close(fd);
	return (0);
}

// Function to handle multiple redirections '>' or '>>'
// Returns 0 on success, -1 on error
int	redir_out(t_dclst *node, t_general *gen)
{
	int		flag;

	if (!node || !gen)
		return (shell_err_msg("redir_out", "invalid arguments"));
	flag = redir_flag(node);
	return (redir_out_from_node(node, gen, flag));
}
