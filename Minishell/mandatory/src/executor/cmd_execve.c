#include "../../include/minishell.h"

// Function to find the path of the executable file in the PATH environment variable
// Returns the path of the executable file if found, otherwise NULL.
// RETURN MUST BE FREED AFTER USAGE.
char	*find_path_in_PATH(char *cmd, char **path_split)
{
	int i;
	char *exec_path;
	char *tmp;

	i = 0;
	while (path_split[i])
	{
		tmp = ft_strjoin(path_split[i], "/");
		if (!tmp)
			return (shell_error_msg(cmd,  "ft_strjoin failed"), NULL);
		exec_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!exec_path)
			return (shell_error_msg(cmd, "ft_strjoin failed"), NULL);
		if (!access(exec_path, F_OK))
			return (exec_path);
		free(exec_path);
		i++;
	}
	return (NULL);
}

// Function to find the path of the executable file in the PATH environment variable
// Returns: The path of the executable file if found, otherwise NULL.
// RETURN MUST BE FREED AFER USAGE.
char*	find_exec_path(char *cmd, char **envp)
{
	char	*path;
	char	**path_split;
	char	*exec_path;

	path = ft_getenv("PATH", envp);
	if (!path)
		return (shell_error_msg(path, "PATH not set"), NULL);
	path_split = ft_split(path, ':');
	if (!path_split)
		return (shell_error_msg(path, "ft_split failed"), NULL);
	exec_path = find_path_in_PATH(cmd, path_split);
	delete_str_tab(path_split);
	return (exec_path);
}

// Function to execute a command using execve
// Returns: 0 on success, -1 on error.
int	execute_cmd(char *path, char **args, char **envp)
{
	pid_t	pid;
	int		status;

	status = -1;
	pid = fork();
	if (pid == -1)
		return (ft_perror(path, "fork failed"), -1);
	if (pid == 0)
	{
		if (execve(path, args, envp) == -1)
			return (ft_perror(path, "exec_ve failed"), status);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			return (ft_perror(path, "waitpid failed"), status);
		if (WIFEXITED(status))
    		return WEXITSTATUS(status);
		if (WIFSIGNALED(status))
   			return 128 + WTERMSIG(status);
	}
	return (status);
}

// Function to execute a non-built-in command using execve
// Returns: 0 on success, -1 on error.
int	execve_cmd(char *cmd, char **args, char **envp)
{
	char	*path;
	int		ret;

	if (!cmd || !args || !envp)
		return (shell_error_msg("execve_cmd", "invalid arguments"), -1);
	if (ft_strchr(cmd, '/'))
	{
		path = ft_strdup(cmd);
		if (!path)
			return (shell_error_msg(cmd, "ft_strdup failed"), -1);
		if (access(path, F_OK))
			return (free(path), shell_error_msg(cmd, "no such file or directory"), -1);
	}
	else
		path = find_exec_path(cmd, envp);
	if (!path)
		return (shell_error_msg(cmd, "command not found"), -1);
	if (access(path, X_OK))
		return (free(path), shell_error_msg(cmd, "permission denied"), -1);
	ret = execute_cmd(path, args, envp);
	free(path);
	return (ret);
}
