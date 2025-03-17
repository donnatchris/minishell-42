/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filenames_searcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:59:51 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 06:04:47 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to find a subpattern in a string
// Returns a pointer to the first occurence of the subpattern in the string
// or NULL if not found
static char	*find_subpattern(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *) big);
	while (big[i])
	{
		j = 0;
		while (big[j + i] == little[j] && big[j + i])
		{
			j++;
			if (j == len)
				return ((char *) big + i);
		}
		i++;
	}
	return (NULL);
}

//test
// Function to find the next wildcard in a pattern
// Returns a pointer to the next wildcard in the pattern
// or a pointer to the end of the pattern if there is no more wildcard
static char	*find_next_wildcard(char *pat_p)
{
	char	*next_wildcard;

	next_wildcard = ft_strchr(pat_p, '*');
	if (!next_wildcard)
		next_wildcard = pat_p + ft_strlen(pat_p);
	return (next_wildcard);
}

// Function to move the pointer pass the wildcards
// and check if the end of a string is reached
// Returns 1 if the end of the string is reached, 0 if not
static int	is_end_of_str(char **pat_p)
{
	while (**pat_p == '*')
		(*pat_p)++;
	if (**pat_p == '\0')
		return (1);
	return (0);
}

// Function to increment two pointers
static void	increment_2_pointers(char **pat_p, char **file_p)
{
	(*pat_p)++;
	(*file_p)++;
}

// Function to check if a filename matches a pattern
// Returns 1 if the filename matches the pattern, 0 if not
int	is_matching_filename(char *pattern, char *filename)
{
	char	*next_wildcard;
	char	*pat_p;
	char	*file_p;

	pat_p = pattern;
	file_p = filename;
	while (*pat_p)
	{
		if (*pat_p == '*')
		{
			if (is_end_of_str(&pat_p))
				return (1);
			next_wildcard = find_next_wildcard(pat_p);
			file_p = find_subpattern(file_p, pat_p, (next_wildcard - pat_p));
			if (!file_p)
				return (0);
			file_p += (next_wildcard - pat_p);
			pat_p = next_wildcard;
			continue ;
		}
		if (*file_p != *pat_p)
			return (0);
		increment_2_pointers(&pat_p, &file_p);
	}
	return (*file_p == '\0');
}
