#include "../../include/minishell.h"

// Function to find a subpattern in a string
// Returns a pointer to the first occurence of the subpattern in the string
// or NULL if not found
static char	*find_subpattern(const char *big, const char *little, size_t little_len)
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
			if (j == little_len)
				return ((char *) big + i);
		}
		i++;
	}
	return (NULL);
}

// Function to check if a filename matches a pattern
// Returns 1 if the filename matches the pattern, 0 if not
static int	is_matching_filename(char *pattern, char *filename)
{
	char	*next_wildcard;
	char	*pat_ptr;
	char	*file_ptr;

	pat_ptr = pattern;
	file_ptr = filename;
	while (*pat_ptr)
	{
		if (*pat_ptr == '*')
		{
			while (*pat_ptr == '*')
				pat_ptr++;
			if (*pat_ptr == '\0')
				return (1);
			next_wildcard = ft_strchr(pat_ptr, '*');
			if (!next_wildcard)
				next_wildcard = pat_ptr + ft_strlen(pat_ptr);
			file_ptr = find_subpattern(file_ptr, pat_ptr, (next_wildcard - pat_ptr));
			if (!file_ptr)
				return (0);
			file_ptr += (next_wildcard - pat_ptr);
			pat_ptr = next_wildcard;
		}
		else
		{
			if (*file_ptr != *pat_ptr)
				return (0);
			pat_ptr++;
			file_ptr++;
		}
	}
	return (*file_ptr == '\0');
}

// Function to extract the filenames that match a pattern
// Returns a string array with the matching filenames or NULL if founds none
// RETURNS MUST BE FREED AFTER USE with delete_str_tab
char	**extract_matching_filenames(char *arg, char **file_array)
{
	char **matching_filenames;
	size_t count;

	matching_filenames = NULL;
	count = 0;
	while (*file_array)
	{
		if (is_matching_filename(arg, *file_array))
		{
			count++;
			matching_filenames = ft_realloc_str_array(matching_filenames, count + 1);
			if (!matching_filenames)
				return (shell_error_msg("extract_matching_filenames", "ft_realloc_str_array failed"), NULL);
			matching_filenames[count - 1] = ft_strdup(*file_array);
			matching_filenames[count] = NULL;
		}
		file_array++;
	}
	return (matching_filenames);
}
