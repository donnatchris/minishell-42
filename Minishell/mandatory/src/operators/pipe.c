#include "../../include/minishell.h"

// Function to handle the pipe operator
// Returns exec_tree(tree->right) on success, -1 on error
int	pipe_operator(t_tree *tree, char ***envp, t_general *gen)
{
	int		fd[2];
	int		stdin_backup;
	pid_t	pid;
	int		status;

	if (!tree || !envp || !gen || !tree->left || !tree->right)
		return (shell_error_msg("handle_pipe", "invalid arguments"));
	if (pipe(fd) == -1)
		return (ft_perror("handle_pipe", "pipe failed"));
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]), ft_perror("handle_pipe", "fork failed"));
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			close(fd[1]);
			exit(ft_perror("handle_pipe", "dup2 failed"));
		}
		close(fd[1]);
		exit(exec_tree(tree->left, envp, gen));
	}
		//test
	close(fd[1]);
	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup == -1)
		return (close(fd[0]), ft_perror("handle_pipe", "dup failed"));
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (close(fd[0]), close(stdin_backup), ft_perror("handle_pipe", "dup2 failed"));
	close(fd[0]);
	status = exec_tree(tree->right, envp, gen);
	if (dup2(stdin_backup, STDIN_FILENO) == -1)
		return (close(stdin_backup), ft_perror("handle_pipe", "dup2 failed"));
	close(stdin_backup);
	if (waitpid(pid, &status, 0) == -1)
		return (ft_perror("handle_pipe", "waitpid failed"));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}
