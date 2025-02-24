#include "../../include/minishell.h"

// Function to handle the AND operator
// Returns the exit status of the last command or -1 in case of error
int	and_operator(t_dclst *node1, t_dclst *node2, char ***envp, t_general *gen)
{
	int		status;

	status = 0;
	if (node1->data)
		status = exec_node(node1, envp, gen);
	if (status == 0 && node2->data)
		status = exec_node(node2, envp, gen);
	return (status);
}

// Function to handle the OR operator
// Returns the exit status of the last command or -1 in case of error
int	or_operator(t_dclst *node1, t_dclst *node2, char ***envp, t_general *gen)
{
	int		status;

	status = 0;
	if (node1->data)
		status = exec_node(node1, envp, gen);
	if (status != 0 && node2->data)
		status = exec_node(node2, envp, gen);
	return (status);
}

// Function to handle the SEMICOLON operator
// Returns the exit status of the last command or -1 in case of error
int	semicolon_operator(t_dclst *node1, t_dclst *node2, char ***envp, t_general *gen)
{
	int		status;

	status = 0;
	if (node1->data)
		status = exec_node(node1, envp, gen);
	if (node2->data)
		status = exec_node(node2, envp, gen);
	return (status);
}
