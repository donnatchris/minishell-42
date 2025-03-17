/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:08:06 by christophed       #+#    #+#             */
/*   Updated: 2025/03/15 10:12:39 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to remove an environment variable from the environment variable list
// Returns 0 on success, -1 on failure
int	unset_one_env_var(char *key, char ***envp)
{
	int		i;
	int		j;
	size_t	len;

	len = ft_strlen(key);
	i = 0;
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], key, len) && ((*envp)[i][len] == '='
			|| (*envp)[i][len] == '\0'))
		{
			j = i;
			free((*envp)[i]);
			while ((*envp)[j])
			{
				(*envp)[j] = (*envp)[j + 1];
				j++;
			}
			return (0);
		}
		i++;
	}
	return (-1);
}

// Function to remove environment variables from the environment variable list
// like the unset command in bash
// Returns 0 on success, -1 on failure
int	unset_cmd(char **args, char ***envp)
{
	int		i;
	char	**key;
	char	*name;

	if (!envp || !*envp || !args)
		return (shell_err_msg("unset", "invalid arguments"));
	i = 1;
	while (args[i])
	{
		if (is_valid_var_name(args[i]))
		{
			key = find_env_var(args[i], *envp);
			if (key)
			{
				name = cut_name(*key);
				if (!name)
					return (-1);
				unset_one_env_var(name, envp);
				free(name);
			}
		}
		i++;
	}
	return (0);
}
