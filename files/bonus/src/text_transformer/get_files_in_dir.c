/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files_in_dir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:26:31 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 05:26:33 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to get the size of a directory
// (excluding hidden files)
// Returns: The number of files in the directory
static size_t	dirsize(char *dirpath, int mode)
{
	DIR				*dir;
	size_t			size;
	struct dirent	*entry;

	dir = opendir(dirpath);
	size = 0;
	if (!dir)
		return (ft_perror("dirsize", "opendir failed"), size);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (mode == NO_HIDDEN && entry->d_name[0] != '.')
			size++;
		else
			size++;
	}
	if (closedir(dir) == -1)
		ft_perror("dirsize", "closedir failed");
	return (size);
}

// Function to copy the file names in the directory to a string array
// (excluding hidden files)
static void	copy_file_names(char **file_array, DIR *dir, size_t len, int mode)
{
	struct dirent	*entry;
	size_t			i;

	i = 0;
	while (i < len)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		else
		{
			if (entry->d_name[0] == '.' && mode == NO_HIDDEN)
				continue ;
			file_array[i] = ft_strdup(entry->d_name);
			if (!file_array[i])
			{
				ft_perror("copy_files_in_dir", "ft_strdup failed");
				break ;
			}
		}
		i++;
	}
	file_array[i] = NULL;
}

// Function to get the files in the current directory
// Returns: A string array with the names of the files in the directory
// or NULL if an error occurs
// RETURN MUST BE FREED AFTER USE with delete_str_tab
char	**get_files_in_dir(char *path, int mode)
{
	char			**file_array;
	DIR				*dir;
	size_t			len;

	len = dirsize(path, mode);
	file_array = (char **) malloc(sizeof(char *) * (len + 1));
	if (!file_array)
		return (ft_perror("get_files_in_dir", "malloc failed"), NULL);
	file_array[len] = NULL;
	dir = opendir(path);
	if (!dir)
		return (ft_perror("get_files_in_dir", "opendir failed"), NULL);
	copy_file_names(file_array, dir, len, mode);
	if (closedir(dir) == -1)
		ft_perror("get_files_in_dir", "closedir failed");
	return (file_array);
}
