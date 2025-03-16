/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:32:29 by christophed       #+#    #+#             */
/*   Updated: 2025/03/16 15:56:56 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to handle the child process (the writing process)
// Returns 0 on success, -1 on error
static int	writing_proc(int fd[], t_tree *tree, t_general *gen)
{
	int	status;

	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		delete_general(gen);
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
static int	reading_proc(int fd[], t_tree *tree, t_general *gen)
{
	int	status;

	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		delete_general(gen);
		ft_perror("handle_pipe", "dup2 failed");
		exit(42);
	}
	close(fd[0]);
	status = exec_tree(tree->right, gen);
	delete_general(gen);
	exit(status);
}

// Function to create all heredoc before applying the pipe
// Returns 0 on success, 1 on error
static int	create_heredoc_from_pipe(t_tree *tree, t_general *gen)
{
	t_tree	*cuurent;

	gen->in_pipe = 1;
	cuurent = tree->left;
	if (!cuurent)
		return (1);
	while (cuurent->type != TREE_COMMAND && cuurent->type != TREE_PARENTHESIS)
	{
		cuurent = cuurent->left;
		if (!cuurent)
			return (1);
	}
	create_heredoc(cuurent->list_node, gen);
	return (0);
}

// Function to close the pipe and wait for the child processes
// Returns the status of the right process or -1 if waitpid fails
static int	close_pipe(int fd[2], int left_pid, int right_pid, t_general *gen)
{
	int		left_status;
	int		right_status;

	gen->in_pipe = 0;
	close(fd[1]);
	close(fd[0]);
	if (waitpid(left_pid, &left_status, 0) == -1)
		ft_perror("handle_pipe", "left waitpid failed");
	if (waitpid(right_pid, &right_status, 0) == -1)
		ft_perror("handle_pipe", "right waitpid failed");
	if (WIFSIGNALED(right_status))
		return (128 + WTERMSIG(right_status));
	if (WIFEXITED(right_status))
		return (WEXITSTATUS(right_status));
	return (-1);
}

// Function to handle the pipe operator
// Returns exec_tree(tree->right) on success, -1 on error
int	pipe_operator(t_tree *tree, t_general *gen)
{
	int		fd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (!tree || !gen || !tree->left || !tree->right)
		return (shell_err_msg("handle_pipe", "invalid arguments"));
	if (pipe(fd) == -1)
		return (ft_perror("handle_pipe", "pipe failed"));
	if (!gen->in_pipe)
		create_heredoc_from_pipe(tree, gen);
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
	return (close_pipe(fd, left_pid, right_pid, gen));
}
