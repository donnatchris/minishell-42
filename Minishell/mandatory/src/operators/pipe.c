#include "../../include/minishell.h"

// Function to handle the end of the pipe
// Returns the exit status of the last command or -1 in case of error
int	end_pipe(pid_t pid[])
{
	int		status;

	if (waitpid(pid[0], NULL, 0) == -1)
		return (ft_perror("pipe_operator", "waitpid failed"));
	if (waitpid(pid[1], &status, 0) == -1)
		return (ft_perror("pipe_operator", "waitpid failed"));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (-1);
}

// Function to handle the writing process
// Returns nothing
void	reading_process(int fd[], t_dclst *node, char ***envp, t_general *gen)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		exit(ft_perror("pipe_operator", "dup2 failed"));
	close(fd[0]);
	exit (exec_node(node, envp, gen));
}
// Function to handle the writing process
// Returns nothing
void	writing_process(int fd[], t_dclst *node, char ***envp, t_general *gen)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		exit(ft_perror("pipe_operator", "dup2 failed"));
	close(fd[1]);
	exit (exec_node(node, envp, gen));
}

// Function to handle the fork failure
// Returns -1
int	fork_fail(int fd[], int pid)
{
	close(fd[0]);
	close(fd[1]);
	if (pid >= 0)
		waitpid(pid, NULL, 0);
	return (ft_perror("pipe_operator", "fork failed"));
}

// Function to handle the pipe operator
// Returns the exit status of the last command or -1 in case of error
int	pipe_operator(t_dclst *node1, t_dclst *node2, char ***envp, t_general *gen)
{
	int	fd[2];
	pid_t	pid[2];

	if (pipe(fd) == -1)
		return (ft_perror("pipe_operator", "pipe failed"));
	pid[0] = fork();
	if (pid[0] == -1)
		return (fork_fail(fd, -1));
	if (pid[0] == 0)
		writing_process(fd, node1, envp, gen);
	pid[1] = fork();
	if (pid[1] == -1)
		return (fork_fail(fd, pid[0]));
	if (pid[1] == 0)
		reading_process(fd, node2, envp, gen);
    close(fd[0]);
    close(fd[1]);
	return (end_pipe(pid));
}


// Tests à faire
// Commandes simples : ls | wc -l, echo "Hello" | cat
// Commande inexistante : ls | commande_inexistante
// Gestion des signaux : sleep 10 | cat + Ctrl+C
// Processus zombie : ls | sleep 10 (ne doit pas rester en mémoire après interruption)




// récursive:
// // Recursive function to handle multiple pipe operators
// int pipe_recursive(t_dclst **commands, int index, int num_commands, int prev_fd, char ***envp, t_general *gen) {
//     int fd[2];
//     pid_t pid;

//     // Base case: if we've reached the last command
//     if (index == num_commands) {
//         return 0; // No more commands to process
//     }

//     // Create a pipe for the current command
//     if (index < num_commands - 1) {
//         if (pipe(fd) == -1) {
//             return ft_perror("pipe_recursive", "pipe failed");
//         }
//     }

//     // Fork the process for the current command
//     pid = fork();
//     if (pid == -1) {
//         if (index > 0) close(fd[0]);
//         if (index < num_commands - 1) close(fd[1]);
//         return ft_perror("pipe_recursive", "fork failed");
//     }

//     if (pid == 0) {
//         // Child process
//         if (prev_fd != -1) {
//             dup2(prev_fd, STDIN_FILENO); // Redirect stdin from the previous pipe
//             close(prev_fd);
//         }
//         if (index < num_commands - 1) {
//             dup2(fd[1], STDOUT_FILENO); // Redirect stdout to the current pipe
//             close(fd[1]);
//         }
//         exec_node(commands[index], envp, gen);
//         exit(ft_perror("pipe_recursive", "exec_node failed"));
//     }

//     // Close the current pipe ends in the parent
//     if (prev_fd != -1) close(prev_fd);
//     if (index < num_commands - 1) close(fd[1]); // Close the write end of the current pipe

//     // Recursively call for the next command
//     return pipe_recursive(commands, index + 1, num_commands, fd[0], envp, gen);
// }

// // Wrapper function to initiate the recursive pipe handling
// int pipe_operators(t_dclst **commands, int num_commands, char ***envp, t_general *gen) {
//     return pipe_recursive(commands, 0, num_commands, -1, envp, gen);
// }