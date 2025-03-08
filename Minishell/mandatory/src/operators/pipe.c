/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:32:29 by christophed       #+#    #+#             */
/*   Updated: 2025/03/08 20:08:02 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to handle the child process (the writing process)
// Returns 0 on success, -1 on error
int	writing_proc(int fd[], t_tree *tree, char ***envp, t_general *gen)
{
	int	status;

	child_signals();
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		exit(ft_perror("handle_pipe", "dup2 failed"));
	}
	close(fd[1]);
	status = exec_tree(tree->left, envp, gen);
	exit(status);
}

// Function to handle the parent process (the reading process)
// Returns the status of the command or -1 if waitpid fails
int	reading_proc(int fd[], t_tree *tree, char ***envp, t_general *gen)
{
	int	stdin_backup;
	int	status;

	close(fd[1]);
	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup == -1)
		return (close(fd[0]), ft_perror("handle_pipe", "dup failed"));
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (close(fd[0]), close(stdin_backup),
			ft_perror("handle_pipe", "dup2 failed"));
	close(fd[0]);
	status = exec_tree(tree->right, envp, gen);
	if (dup2(stdin_backup, STDIN_FILENO) == -1)
		return (close(stdin_backup), ft_perror("handle_pipe", "dup2 failed"));
	close(stdin_backup);
	return (status);
}

// Function to handle the pipe operator
// Returns exec_tree(tree->right) on success, -1 on error
int	pipe_operator(t_tree *tree, char ***envp, t_general *gen)
{
	int		fd[2];
	pid_t	pid;
	int		child_status;
	int		status;

	if (!tree || !envp || !gen || !tree->left || !tree->right)
		return (shell_err_msg("handle_pipe", "invalid arguments"));
	if (pipe(fd) == -1)
		return (ft_perror("handle_pipe", "pipe failed"));
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]),
			ft_perror("handle_pipe", "fork failed"));
	if (pid == 0)
		writing_proc(fd, tree, envp, gen);
	ignore_signals();
	status = reading_proc(fd, tree, envp, gen);
	if (waitpid(pid, &child_status, 0) == -1)
		return (ft_perror("handle_pipe", "waitpid failed"));
	init_signals();
	if (WIFSIGNALED(child_status))
		return (128 + WTERMSIG(child_status));
	return (status);
}
