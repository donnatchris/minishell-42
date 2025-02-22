#include "../../include/minishell.h"
//test
// Function to reallocate the environment variable array
// Returns a pointer to the new environment array, or NULL on failure
// THE RETURNED ARRAY MUST BE DELETED WITH delete_str_tab
char	**ft_realloc_env(char ***envp, char *new_entry)
{
	char	**new_envp;
	size_t	size;
	size_t	i;

	if (!envp)
		return (ft_putstr_fd("ft_realloc_env: invalid arguments", 2), NULL);
	size = count_env_size(*envp);
	new_envp = (char **) malloc(sizeof(char *) * (size + 2));
	if (!new_envp)
		return (perror("copy_env: malloc failed\n"), NULL);
	i = 0;
	while ((*envp)[i])
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		if (!new_envp[i])
		{
			delete_str_tab(new_envp);
			return (ft_putstr_fd("copy_env: ft_strdup failed\n", 2), NULL);
		}
		i++;
	}
	new_envp[i] = ft_strdup(new_entry);
	new_envp[i + 1] = NULL;
	delete_str_tab(*envp);
	*envp = new_envp;
	return (*envp);
}

// Function to add a new variable to the environment
// from a key but without a value
// Returns 0 on success, -1 on failure
int	create_env_var_void(const char *key, char sep, char ***envp)
{
	char	*new_entry;

	if (!envp || !key)
		return (ft_putstr_fd("create_env_var_void: invalid arguments\n", 2), -1);
	if (sep == '=')
		new_entry = ft_strjoin(key, "=");
	else
		new_entry = ft_strdup(key);
	if (!new_entry)
		return (ft_putstr_fd("create_env_var_void: ft_strjoin or ft_strdup failed\n", 2), -1);
	if (!ft_realloc_env(envp, new_entry))
		return (free(new_entry), -1);
	free(new_entry);
	return (0);
}

// Function to add a new variable to the environment
// from a key and a value
// Returns 0 on success, -1 on failure
int	create_env_var(const char *key, char sep, const char *value, char ***envp)
{
	char	*temp;
	char	*new_entry;
	char	**new_envp;
	size_t	size;

	if (!envp || !key)
		return (ft_putstr_fd("create_env_var: invalid arguments\n", 2), -1);
	if (!value)
		return (create_env_var_void(key, sep, envp));
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (ft_putstr_fd("create_env_var: ft_strjoin or ft_strdup failed\n", 2), -1);
	new_entry = ft_strjoin(temp, value);
	free(temp);
	if (!new_entry)
		return (ft_putstr_fd("create_env_var: strjoin failed\n", 2), -1);
	size = count_env_size(*envp);
	new_envp = ft_realloc_env(envp, new_entry);
	if (!new_envp)
		return (free(new_entry), ft_putstr_fd("create_env_var: realloc failed\n", 2), -1);
	new_envp[size] = new_entry;
	new_envp[size + 1] = NULL;
	*envp = new_envp;
	return (0);
}

// Function to update an existing variable in the environment
// Returns 0 on success, -1 on failure
int	update_env_var(const char *key, char sep, const char *value, char ***envp)
{
	char	**var;
	char	*temp;
	char	*new_entry;

	if (!envp || !key)
		return (ft_putstr_fd("update_env_var: invalid arguments\n", 2), -1);
	var = find_env_var(key, *envp);
	if (!var)
		return(create_env_var(key, sep, value, envp));
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (ft_putstr_fd("update_env_var: strjoin failed\n", 2), -1);
	if (!value)
		new_entry = ft_strdup(temp);
	else
		new_entry = ft_strjoin(temp, value);
	free(temp);
	if (!new_entry)
		return (ft_putstr_fd("update_env_var: strjoin failed\n", 2), -1);
	free(*var);
	*var = new_entry;
	return (0);
}

// Function to make a dynamicly allocated copy of the environment
// Returns a pointer to the new environment array, or NULL on failure
// THE RETURNED ARRAY MUST BE DELETED WITH delete_str_tab
char	**copy_env(char **envp)
{
	char	**new_envp;
	size_t	size;
	size_t	i;

	if (!envp)
		return (ft_putstr_fd("copy_env: invalid arguments", 2), NULL);
	size = count_env_size(envp);
	new_envp = (char **) malloc(sizeof(char *) * (size + 1));
	if (!new_envp)
		return (perror("copy_env: malloc failed"), NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			delete_str_tab(new_envp);
			return (ft_putstr_fd("copy_env: ft_strdup failed\n", 2), NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
