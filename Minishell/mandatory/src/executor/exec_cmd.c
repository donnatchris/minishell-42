#include "../../include/minishell.h"

// Function to execute a soft buitlin command 
// (meaning it cannot modify the environment variables)
// Returns the exit status of the command
int exec_soft_builtin(int (*function)(char **args, char **envp), char **args, char **envp)
{
	return (function(args, envp));
}

// Function to check if the command is a soft builtin
// (meaning it cannot modify the environment variables)
// Returns the function pointer to the builtin or NULL if it is not a hard builtin
int	(*soft_builtin(char *cmd))(char **args, char **envp)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", 4) && len == 4)
		return (echo_cmd);
	else if (!ft_strncmp(cmd, "env", 3) && len == 3)
		return (env_cmd);
	else if (!ft_strncmp(cmd, "pwd", 3) && len == 3)
		return (pwd_cmd);
	return (NULL);
}

// Function to execute a hard buitlin command 
// (meaning it can modify the environment variables)
// Returns the exit status of the command
int exec_hard_builtin(int (*function)(char **args, char ***envp), char **args, char ***envp)
{
	return (function(args, envp));
}

// Function to check if the command is a hard builtin
// (meaning it can modify the environment variables)
// Returns the function pointer to the builtin or NULL if it is not a hard builtin
int	(*hard_builtin(char *cmd))(char **args, char ***envp)
{
	size_t	len;

	len = ft_strlen(cmd);

	if (!ft_strncmp(cmd, "export", 6) && len == 6)
		return (export_cmd);
	else if (!ft_strncmp(cmd, "unset", 5) && len == 5)
		return (unset_cmd);
	return (NULL);
}

// Function to execute a command taking a node as the command
// and the followin nodes as arguments
// Returns the exit status of the command
int	exec_cmd(t_dclst *node, char ***envp, t_general *gen)
{
	char	**args;
	int		status;
	int		(*hard_built_func)(char **, char ***);
	int		(*soft_built_func)(char **, char **);

	if (!node || !envp)
		return (shell_error_msg("exec_node", "invalid argument"));
	status = 0;
	args = extract_args(node, *envp, gen);
	// args = manage_wildcards(args);
	if (!args)
		return (shell_error_msg("exec_node", "extract_args failed"), -1);
	if (!ft_strncmp(args[0], "exit", 4) && ft_strlen(args[0]) == 4)
		exit_cmd(args, *envp, gen);
	else if (!ft_strncmp(args[0], "cd", 2) && ft_strlen(args[0]) == 2)
		status = cd_cmd(args, envp, gen);
	else
	{
		hard_built_func = hard_builtin(args[0]);
		soft_built_func = soft_builtin(args[0]);
		if (hard_built_func)
			status = exec_hard_builtin(hard_built_func, args, envp);
		else if (soft_built_func)
			status = exec_soft_builtin(soft_built_func, args, *envp);
		else
			status = execve_cmd(args[0], args, *envp);
	}
	delete_str_tab(args);
	return (status);
}
