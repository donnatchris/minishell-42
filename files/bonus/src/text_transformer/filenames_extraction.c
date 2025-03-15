/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_matching_filenames.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:27:03 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 06:00:27 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to extract the filenames that match a pattern
// Returns a string array with the matching filenames or NULL if founds none
// RETURNS MUST BE FREED AFTER USE with delete_str_tab
char	**extract_matching_filenames(char *arg, char **file_array)
{
	char	**matching_files;
	size_t	count;

	matching_files = NULL;
	count = 0;
	while (*file_array)
	{
		if (is_matching_filename(arg, *file_array))
		{
			count++;
			matching_files = ft_realloc_str_array(matching_files, count + 1);
			if (!matching_files)
				return (shell_err_msg("extract_matching_filenames",
						"ft_realloc_str_array failed"), NULL);
			matching_files[count - 1] = ft_strdup(*file_array);
			matching_files[count] = NULL;
		}
		file_array++;
	}
	return (matching_files);
}
