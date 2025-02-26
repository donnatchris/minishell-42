#include "../../include/minishell.h"

// Function to run a minishell inside the minishell
// Returns the status of the last command or -1 on error
int	mini_minishell(t_dclst **head, char **envp, t_general *gen)
{
	t_tree	*tree;
	int		status;

	tree = create_tree(*head, (*head)->prev->prev);
	status = exec_tree(tree, &envp, gen);
	delete_tree(tree);
	return (status);
}

// Function to run a parenthesis node
// Returns 0 on success, -1 on error
int	run_parenthesis(t_tree *tree, char ***envp, t_general *gen)
{
	int		status;
	pid_t	pid;
	t_dclst	**head;


	if (!tree || !envp || !gen)
		return (shell_error_msg("run_parenthesis", "invalid arguments"), -1);
	pid = fork();
	if (pid == -1)
		return (ft_perror("run_parenthesis", "fork failed"), -1);
	if (pid == 0)
	{
		head = tokenize(((t_token *) tree->list_node->data)->start);
		if (check_syntax(head) == -1)
			return (-1);
		status = mini_minishell(head, *envp, gen);
		dclst_clear(head);
		exit(status);
	}
	if (waitpid(pid, &status, 0) == -1)
		return (ft_perror("run_parenthesis", "waitpid failed"), -1);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

