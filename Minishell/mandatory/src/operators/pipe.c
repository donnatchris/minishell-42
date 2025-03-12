/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:32:29 by christophed       #+#    #+#             */
/*   Updated: 2025/03/12 12:59:57 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to handle the child process (the writing process)
// Returns 0 on success, -1 on error
int	writing_proc(int fd[], t_tree *tree, t_general *gen)
{
	int	status;

	child_signals();
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		delete_general(gen);
		// close(STDOUT_FILENO);
		ft_perror("handle_pipe", "dup2 failed");
		exit(42);
	}
	close(fd[1]);
	status = exec_tree(tree->left, gen);
	delete_general(gen);
	exit(status);
}

// Function to handle the parent process (the reading process)
// Returns the status of the command or -1 if waitpid fails
int	reading_proc(int fd[], t_tree *tree, t_general *gen)
{//test
	int	status;

	child_signals();
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		delete_general(gen);
		// close(STDIN_FILENO);
		ft_perror("handle_pipe", "dup2 failed");
		exit(42);
	}
	close(fd[0]);
	status = exec_tree(tree->right, gen);
	delete_general(gen);
	exit(status);
}

// Function to handle the pipe operator
// Returns exec_tree(tree->right) on success, -1 on error
int	pipe_operator(t_tree *tree, t_general *gen)
{
	int		fd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		left_status;
	int		right_status;

	if (!tree || !gen || !tree->left || !tree->right)
		return (shell_err_msg("handle_pipe", "invalid arguments"));
	if (pipe(fd) == -1)
		return (ft_perror("handle_pipe", "pipe failed"));
	left_pid = fork();
	if (left_pid == -1)
		return (close(fd[0]), close(fd[1]),
			ft_perror("handle_pipe", "fork failed"));
	if (left_pid == 0)
		writing_proc(fd, tree, gen);
		
	right_pid = fork();
	if (right_pid == -1)
		return (close(fd[0]), close(fd[1]),
			ft_perror("handle_pipe", "fork failed"));
	if (right_pid == 0)
		reading_proc(fd, tree, gen);
	close(fd[0]);
	close(fd[1]);
	ignore_signals();
	if (waitpid(left_pid, &left_status, 0) == -1)
		ft_perror("handle_pipe", "waitpid failed");
	if (waitpid(right_pid, &right_status, 0) == -1)
		ft_perror("handle_pipe", "waitpid failed");
	init_signals();
	if (WIFSIGNALED(right_status))
		return (128 + WTERMSIG(right_status));	
	return (WIFEXITED(right_status) ? WEXITSTATUS(right_status) : -1);
}
