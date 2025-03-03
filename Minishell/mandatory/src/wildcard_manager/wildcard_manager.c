#include "../../include/minishell.h"

// Function to moves the lines of an array of strings up
// from the index arg_index to the index new_size
void	move_lines_up(char **arg_array, size_t arg_index, size_t new_size)
{
	size_t	i;

	i = new_size;
	while (i > arg_index)
	{
		arg_array[i] = arg_array[i - 1];
		i--;
	}
}

// Function to replace an argument in the arg_array with the matching filenames
void	replace_arg(char **arg_array, size_t arg_index, char **matching_array)
{
	size_t	new_size;

	new_size = count_env_size(arg_array) + count_env_size(matching_array) - 1;
	arg_array = ft_realloc_str_array(arg_array, new_size + 1);
	if (!arg_array)
	{
		delete_str_tab(matching_array);
		shell_error_msg("replace_arg", "ft_realloc_str_array failed");
		return ;
	}
	if (*matching_array)
	{
		free(arg_array[arg_index]);
		arg_array[arg_index] = ft_strdup(*matching_array);
		arg_index++;
		matching_array++;
	}
	while (*matching_array)
	{
		move_lines_up(arg_array, arg_index, new_size);
		arg_array[arg_index] = ft_strdup(*matching_array);
		arg_index++;
		matching_array++;
	}
}

// Function to find the mode for the extract_matching_filenames() function
// Returns W_HIDDEN if the argument starts with a '.', NO_HIDDEN otherwise
int	find_mode(char *arg)
{
	if (arg[0] == '.')
		return (W_HIDDEN);
	return (NO_HIDDEN);
}

// Function to manage the wildcards in a dynamicallly allocated array of strings
void	manage_wildcards(char **arg_array)
{
	size_t	i;
	char	**file_array;
	char	**matching_array;

	i = -1;
	while (arg_array[++i])
	{
		if (ft_strchr(arg_array[i], '*'))
		{
			file_array = get_files_in_dir(arg_array[i], find_mode(arg_array[i]));
			if (!file_array)
				continue ;
			matching_array = extract_matching_filenames(arg_array[i], file_array);
			delete_str_tab(file_array);
			if (matching_array)
			{
				replace_arg(arg_array, i, matching_array);
				delete_str_tab(matching_array);
			}
		}
	}
}

// *			Remplace 0 ou plusieurs caractères
// *.txt		Tous les fichiers se terminant par .txt
// file*		Tous les fichiers commençant par file
// *file*		Tous les fichiers contenant file
// *.*			Tous les fichiers ayant une extension