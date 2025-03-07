/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:52:40 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 10:46:58 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to find the next heredoc
// Returns the node found or NULL if nothing is found
static t_dclst	*next_heredoc(t_dclst *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	while (1)
	{
		node = node->next;
		token = (t_token *) node->data;
		if (token->type == TOKEN_HEREDOC)
			return (node);
		if (!is_text(node))
			break ;
	}
	return (NULL);
}

// Function to count the number of delimiters
// Returns the number found
static size_t	count_delimiters(t_dclst *node)
{
	size_t	size;

	size = 1;
	while (1)
	{
		node = next_heredoc(node);
		if (!node)
			break ;
		size++;
	}
	return (size);
}

// Function to find the delimiters and create an array
// Returns the next heredoc node, NULL if there is no more heredoc
static char	**find_delimiters(t_dclst *node)
{
	char	**delimiters;
	size_t	size;
	size_t	i;

	size = count_delimiters(node);
	delimiters = (char **) malloc(sizeof(char *) * size + 1);
	if (!delimiters)
		return (ft_perror("find_delimiters", "malloc failed"), NULL);
	delimiters[0] = ft_strdup(((t_token *) node->next->data)->start);
	i = 1;
	while (1)
	{
		delimiters[i] = NULL;
		node = next_heredoc(node);
		if (!node)
			break ;
		delimiters[i] = ft_strdup(((t_token *) node->next->data)->start);
		i++;
	}
	return (delimiters);
}

// Function to handle multiple heredoc redirections '<<'
// return 0 on success, return -1 on failure
int	redir_heredoc(t_dclst *node, char ***envp, t_general *gen)
{
	pid_t	pid;
	int		pipefd[2];
	char	**delimiters;

	if (!node || !envp || !gen)
		return (shell_err_msg("redir_heredoc", "invalid arguments"));
	if (pipe(pipefd) == -1)
		return (ft_perror("redir_heredoc", "pipe failed"));
	pid = fork();
	if (pid == -1)
		return (ft_perror("redir_heredoc", "fork failed"));
	delimiters = find_delimiters(node);
	if (pid == 0)
	{
		heredoc_signals();
		if (!delimiters)
			exit(-1);
		redir_heredoc_read(pipefd, delimiters, *envp, gen);
	}
	ignore_signals();
	delete_str_tab(delimiters);
	waitpid(pid, NULL, 0);
	init_signals();
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		return (close(pipefd[0]), ft_perror("redir_heredoc", "dup2 failed"));
	return (close(pipefd[0]), 0);
}
