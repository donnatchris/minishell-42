#include "../../include/minishell.h"

// Function to handle the pipe operator
int	pipe_operator(t_dclst *node1, t_dclst *node2, char ***envp, t_general *gen)
{
	int	fd[2];
	int	id;

	if (pipe(fd) == -1)
		return (ft_perror("pipe_operator", "pipe failed"));
	id = fork();
	if (id == -1)
		return (ft_perror("pipe_operator", "fork failed"));
	if (id == 0)
	{
		// child (fd = 1 is stdout: it writes to the pipe)
		close(fd[0]);
		exec_node(node1, envp, gen);
		close(fd[1]);
	}
	else
	{
		// parent (fd = 0 is stdin: it reads from the pipe)
		close(fd[1]);
		exec_node(node2, envp, gen);
		close(fd[0]);
	}
}
