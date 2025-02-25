#include "../../include/minishell.h"

// Function to update or create PWD and OLDPWD in the environment variables
// Returns 0 on success, -1 on failure
void	actualize_cd_env(char *oldpwd, char ***envp)
{
	char	pwd[PATH_MAX];

	if (update_env_var("OLDPWD", '=', oldpwd, envp) == -1)
		shell_error_msg("cd", "failed to create OLDPWD");
	if (update_env_var("PWD", '=', getcwd(pwd, sizeof(pwd)), envp) == -1)
		shell_error_msg("cd", "failed to create PWD");
}

// Function to go the actual dir
// Returns a pointer to the path
// Returns NULL on failure
char	*find_actual_dir(void)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, sizeof(pwd)))
		return (shell_error_msg("cd", "getcwd failed"), NULL);
	return (ft_strdup(pwd));
}

// Function to change directory to the parent directory
// Returns a pointer to the path
// Returns NULL on failure
char	*find_parent_dir(void)
{
	char	pwd[PATH_MAX];
	char	*ptr;

	if (!getcwd(pwd, sizeof(pwd)))
		return (shell_error_msg("cd", "getcwd failed"), NULL);
	ptr = ft_strrchr(pwd, '/');
	if (ptr == NULL)
		return (shell_error_msg("cd", "invalid path"), NULL);
	if (ptr == pwd)
		return (ft_strdup("/"));
	else
		*ptr = '\0';
	return (ft_strdup(pwd));
}

// Function to find the path for the cd command
// Returns a pointer to the path
// Returns NULL on failure
char	*find_cd_path(char *input, char **envp, char *home, char *old)
{

	if (!input || *input == '\0')
		input = home;
	if (!ft_strncmp(input, "..", 2) && ft_strlen(input) == 2)
		return (find_parent_dir());
	else if (!ft_strncmp(input, ".", 1) && ft_strlen(input) == 1)
		return (find_actual_dir());
	else if (input[0] == '~')
	{
		if (!home)
			return (shell_error_msg("cd", "HOME not set"), NULL);
		return (ft_strjoin(home, input + 1));
	}
	else if (!ft_strncmp(input, "-", 1))
	{
		if (!old)
			return (shell_error_msg("cd", "OLDPWD not set"), NULL);
		else
			return (ft_strdup(ft_getenv("OLDPWD", envp)));
	}
	else
		return (ft_strdup(input));
}

// Function to change working directory like the cd command in bash
// and properly update the environment variables
// Returns 0 on success, -1 on failure
int	cd_cmd(char **args, char ***envp)
{
	char	pwd[PATH_MAX];
	char	*new_pwd;
	char	*path;
	char	*home;
	char	*old;

	if (!args || !envp || !args[0])
		return (shell_error_msg("cd", "invalid arguments"));
	home = ft_getenv("HOME", *envp);
	old = ft_getenv("OLDPWD", *envp);
	if (!getcwd(pwd, sizeof(pwd)))
		return (shell_error_msg("cd", "getcwd failed"));
	path = args[1];
	new_pwd = find_cd_path(path, *envp, home, old);
	if (!new_pwd)
		return (-1);
	if (chdir(new_pwd) == -1)
		return  (free(new_pwd), ft_perror("cd", args[1]));
	actualize_cd_env(pwd, envp);
	return (free(new_pwd), 0);
}
