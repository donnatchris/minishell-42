#include "../../include/minishell.h"

// Function to reallocate the environment variable array
// Returns a pointer to the new environment array, or NULL on failure
char	**ft_realloc_env(char **envp, size_t new_size)
{
    char	**new_envp;
    size_t	i;

	i = 0;
    new_envp = (char **) malloc(sizeof(char *) * (new_size + 1));
    if (!new_envp)
        return (NULL);
    if (envp)
    {
		while (envp[i])
		{
            new_envp[i] = envp[i];
			i++;
		}
        free(envp);
    }
    new_envp[i] = NULL;
    return (new_envp);
}

// Function to add a new variable to the environment
// from a key and a value
// Returns 0 on success, -1 on failure
int	create_env_var(const char *key, const char *value, char ***envp)
{
	char	*temp;
	char	*new_entry;
	char	**new_envp;
	size_t	size;

	if (!envp || !key || !value)
		return (ft_putstr_fd("create_env_var: invalid arguments\n", 2), -1);
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (ft_putstr_fd("create_env_var: strjoin failed\n", 2), -1);
	new_entry = ft_strjoin(temp, value);
	if (!new_entry)
		return (free(temp), ft_putstr_fd("create_env_var: strjoin failed\n", 2), -1);
	free(temp);
	size = count_env_size(*envp);
	new_envp = ft_realloc_env(*envp, size + 1);
	if (!new_envp)
		return (free(new_entry), ft_putstr_fd("create_env_var: realloc failed\n", 2), -1);
	new_envp[size] = new_entry;
	new_envp[size + 1] = NULL;
	*envp = new_envp;
	return (0);
}

// Function to update an existing variable in the environment
// Returns 0 on success, -1 on failure
int	update_env_var(const char *key, const char *value, char **envp)
{
	char	**var;
	char	*temp;
	char	*new_entry;

	if (!envp || !key || !value)
		return (ft_putstr_fd("update_env_var: invalid arguments\n", 2), -1);
	var = find_env_var(key, envp);
	if (!var)
		return(create_env_var(key, value, &envp));
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (ft_putstr_fd("update_env_var: strjoin failed\n", 2), -1);
	new_entry = ft_strjoin(temp, value);
	if (!new_entry)
		return (free(temp), ft_putstr_fd("update_env_var: strjoin failed\n", 2), -1);
	free(temp);
	*var = new_entry;
	return (0);
}

// Function to free the environment array
void	delete_env(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

// Function to make a dynamicly allocated copy of the environment
// Returns a pointer to the new environment array, or NULL on failure
char	**copy_env(char **envp)
{
	char	**new_envp;
	size_t	size;
	size_t	i;

	size = count_env_size(envp);
	new_envp = (char **) malloc(sizeof(char *) * (size + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			delete_env(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
