/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:27:52 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 20:56:24 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Function to reallocate a string array
// Returns the new string array
// RETURN MUST BE FREED AFTER USE
char **ft_realloc_str_array(char **tab, size_t new_size)
{
	char **new_tab;
	size_t i;

	if (new_size == 0)
		return (delete_str_tab(tab), NULL);
	new_tab = (char **) malloc(sizeof(char *) * new_size);
	if (!new_tab)
		return (NULL);
	i = 0;
	if (tab)
	{
		while (tab[i] && i < new_size)
		{
			new_tab[i] = tab[i];
			i++;
		}
	}
	while (i < new_size)
	{
		new_tab[i] = NULL;
		i++;
	}
	free(tab);
	return new_tab;
}

// Function to cut the variable name from the string
// Returns the variable name or NULL if the string is invalid
char	*cut_name(char *str)
{
	char	*name;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_substr(str, 0, i);
	if (!name)
		return (shell_err_msg("cut_name", "ft_sustr failed"), NULL);
	return (name);
}

// Function to check is the string is a valid variable name
// Return 1 if the string is valid, 0 if not
int	is_valid_var_name(char *str)
{
	if (!str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}
