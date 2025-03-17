/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:27:53 by christophed       #+#    #+#             */
/*   Updated: 2025/03/16 16:21:48 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to reallocate the environment variable array
// Returns a pointer to the new environment array, or NULL on failure
// THE RETURNED ARRAY MUST BE DELETED WITH delete_str_tab
char	**ft_realloc_env(char ***envp, char *new_entry)
{
	char	**new_envp;
	size_t	i;

	if (!envp)
		return (shell_err_msg("ft_realloc_env", "invalid arguments"), NULL);
	new_envp = (char **) malloc(sizeof(char *) * (count_array_size(*envp) + 2));
	if (!new_envp)
		return (shell_err_msg("copy_env", "malloc failed"), NULL);
	i = 0;
	while ((*envp)[i])
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		if (!new_envp[i])
		{
			delete_str_tab(new_envp);
			return (shell_err_msg("copy_env", "ft_strdup failed"), NULL);
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
int	create_env_var(const char *key, char sep, const char *value, char ***envp)
{
	char	*new_entry;
	char	*temp;

	if (!envp || !key)
		return (shell_err_msg("create_env_var_void", "invalid arguments"));
	if (sep != '=')
		new_entry = ft_strdup(key);
	else
	{
		new_entry = ft_strjoin(key, "=");
		if (value)
		{
			temp = new_entry;
			new_entry = ft_strjoin(new_entry, value);
			free(temp);
		}
	}
	if (!new_entry)
		return (shell_err_msg("create_env_var_void",
				"ft_strjoin or ft_strdup failed"));
	if (!ft_realloc_env(envp, new_entry))
		return (free(new_entry), -1);
	free(new_entry);
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
		return (shell_err_msg("update_env_var", "invalid arguments"));
	var = find_env_var(key, *envp);
	if (!var)
		return (create_env_var(key, sep, value, envp));
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (shell_err_msg("update_env_var", "strjoin failed"));
	if (!value)
		new_entry = ft_strdup(temp);
	else
		new_entry = ft_strjoin(temp, value);
	free(temp);
	if (!new_entry)
		return (shell_err_msg("update_env_var", "strjoin failed"));
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
		return (shell_err_msg("copy_env", "invalid arguments"), NULL);
	size = count_array_size(envp);
	new_envp = (char **) malloc(sizeof(char *) * (size + 1));
	if (!new_envp)
		return (shell_err_msg("copy_env:", "malloc failed"), NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			delete_str_tab(new_envp);
			return (shell_err_msg("copy_env", "ft_strdup failed"), NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
