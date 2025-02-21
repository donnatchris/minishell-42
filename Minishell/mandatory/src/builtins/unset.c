#include "../../include/minishell.h"

// Function to print error message of unset_cmd
// Returns -1
void	print_unset_error(char *arg)
{
	ft_putstr_fd("unset : `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

// Function to realloc memory
// Returns 0 on success, -1 on failure
int	my_realloc(void **ptr, int old_size, int new_size)
{
	void	*new_ptr;
	int		min_size;

	if (!ptr)
		return (-1);
	if (new_size == 0)
	{
		free(*ptr);
		*ptr = NULL;
		return (0);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (-1);
	if (*ptr != NULL)
	{
		if (old_size < new_size)
			min_size = old_size;
		else
			min_size = new_size;
		ft_memcpy(new_ptr, *ptr, min_size);
		free(*ptr);
	}
	*ptr = new_ptr;
	return (0);
}

// Function to remove an environment variable from the environment variable list
// Returns 0 on success, -1 on failure
int	unset_one_env_var(char *key, char ***envp)
{
	int	i;
	int	j;
	// int	size;

	i = 0;
	// size = count_env_size(*envp);
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], key, ft_strlen(key)) && ((*envp)[i][ft_strlen(key)] == '=' || (*envp)[i][ft_strlen(key)] == '\0'))
		{
			j = i;
			free((*envp)[i]);
			while ((*envp)[j])
			{
				(*envp)[j] = (*envp)[j + 1];
				j++;
			}
			// if (my_realloc((void **)(*envp), size * sizeof(char *), (size - 1)  * sizeof(char *)) == -1)
			// 	return (ft_putstr_fd("unset_one_env var: realloc failed", 2), -1);
			return (0);
		}
		i++;
	}
	return (ft_putstr_fd ("unset_one_env var: key not found", 2), -1);
}

// Function to remove environment variables from the environment variable list
// like the unset command in bash
// Returns 0 on success, -1 on failure
int	unset_cmd(char **args, char ***envp)
{
	int		i;
	char	**key;
	char	*name;

	if (!envp || !args)
		return (ft_putstr_fd("unset: invalid arguments\n", 2), -1);
	i = 0;
	while (args[i])
	{
		if (is_valid_var_name(args[i]))
		{
			key = find_env_var(args[i], *envp);
			if (key)
			{
				name = cut_name(*key);
				if (!name)
					return (ft_putstr_fd("unset_cmd: cut_name failed\n", 2), -1);
				unset_one_env_var(name, envp);
				free(name);
			}
			else
				print_unset_error(args[i]);
		}
		else
			print_unset_error(args[i]);
		i++;
	}
	return (0);
}
