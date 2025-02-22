#include "../../include/minishell.h"

// Function to execute a command taking a node as the command
// and the followin nodes as arguments
// Returns the exit status of the command
int	exec_node(t_dclst *node, char ***envp)
{
	char	*cmd;
	char	**args;
	int		status;

	if (!node || !envp)
		return (shell_error_msg("first_try", "Invalid argument"));
	(void)envp;
	cmd = extract_cmd(node, *envp);		// malloc cmd
	args = extract_args(node, *envp);	// malloc args


	ft_printf("CMD= %s\n", cmd);
	status = echo_cmd(args, *envp);



	free(cmd);							// free cmd
	delete_str_tab(args);				// free args
	return (status);
}
