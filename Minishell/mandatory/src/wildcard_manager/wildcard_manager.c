#include "../../include/minishell.h"

// Function to increment 2 size_t variables
void	increment_2_sizet(size_t *i, size_t *j)
{
	(*i)++;
	(*j)++;
}

// Function to copy the file names in the string array
void	concatenate_arrays(char **arg_array, size_t arg_index, char **matching_array, char **new_array)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (i < arg_index)
	{
		new_array[i] = ft_strdup(arg_array[i]);
		i++;
	}
	j = 0;
	k = i;
	while (matching_array[j])
	{
		new_array[k] = ft_strdup(matching_array[j]);
		increment_2_sizet(&j, &k);
	}
	i++;
	while (arg_array[i])
	{
		new_array[k] = ft_strdup(arg_array[i]);
		increment_2_sizet(&i, &k);
	}
	new_array[k] = NULL;
}

// Function to create a new string_array
// It takes the arg array and replace the arg_index element
// with the strings of the matching_array
// Returns the new string array or NULL on failure
// RETURN MUST BE FREED AFTER USE
char	**replace_args(char **arg_array, size_t arg_index, char **matching_array)
{
	char	**new_array;
	size_t	new_size;

	new_size = count_env_size(arg_array) + count_env_size(matching_array) - 1;
	new_array = (char **) malloc(sizeof(char * ) * (new_size + 1));
	if (!new_array)
		return (shell_error_msg("replace_args", "malloc failed"), NULL);
	ft_memset(new_array, 0, sizeof(char *) * (new_size + 1));
	concatenate_arrays(arg_array, arg_index, matching_array, new_array);
	return (new_array);
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
// It takes the array of strings and replaces the strings with wildcards
// with the matching filenames
// Returns the new array of strings or NULL on failure
// RETURN MUST BE FREED AFTER USE
char	**manage_wildcards(char **arg_array)
{
	size_t	i;
	char	**file_array;
	char	**matching_array;
	char	**new_array;
	char	pwd[PATH_MAX];

	i = 0;
	while (arg_array[i])
	{
		if (ft_strchr(arg_array[i], '*'))
		{
			if ((!ft_strncmp(arg_array[0], "export", 6) && ft_strlen(arg_array[0]) == 6) && ft_strchr(arg_array[i], '='))
			{
				i++;
				continue ;
			}
			file_array = get_files_in_dir(getcwd(pwd, sizeof(pwd)), find_mode(arg_array[i]));
			if (!file_array)
			{
				i++;
				continue ;
			}
			matching_array = extract_matching_filenames(arg_array[i], file_array);
			if (matching_array)
			{
				new_array = NULL;
				new_array = replace_args(arg_array, i, matching_array);
				delete_str_tab(matching_array);
			}
			delete_str_tab(file_array);
			if (new_array)
			{
				delete_str_tab(arg_array);
				arg_array = new_array;
			}
		}
		i++;
	}
	return (arg_array);
}

// *			Remplace 0 ou plusieurs caractères
// *.txt		Tous les fichiers se terminant par .txt
// file*		Tous les fichiers commençant par file
// *file*		Tous les fichiers contenant file
// *.*			Tous les fichiers ayant une extension