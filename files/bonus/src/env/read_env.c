/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:23:26 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 04:23:29 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (!ft_strncmp(envp[i], var, len) && (envp[i][len] == '='
			|| envp[i][len] == '\0'))
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

// Function to compare environment variables
// Returns 0 if the variables are equal
// Returns a positive number if s1 is greater than s2
// Returns a negative number if s1 is less than s2
int	compare_env_vars(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 != '=' && *s2 != '=' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == '=' || *s2 == '=')
		return (*s1 - *s2);
	return (*s1 - *s2);
}
