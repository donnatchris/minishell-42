#include "../../include/minishell.h"

// Function to count environment size
// Returns the number of variables in the environment
size_t	count_env_size(char **envp)
{
	size_t	i;

	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
		i++;
	return (i);
}

// Function to find a variable in the environment
// Returns a pointer to the variable in the environment
// so that it can be updated
// Returns NULL if the variable is not found
char	**find_env_var(const char *var, char **envp)
{
	size_t	len;
	int		i;

	if (!var || !envp)
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len) && envp[i][len] == '=')
			return (&envp[i]);
		i++;
	}
	return (NULL);
}

// Function to get the value of an environment variable
// Returns a pointer to the value of the variable
// Returns NULL if the variable is not found
char	*ft_getenv(const char *var, char **envp)
{
	size_t	len;
	int		i;

	if (!var || !envp)
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}
