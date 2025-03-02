#include "../../include/minishell.h"

void	replace_a_line(char *line, char **args, char **file_array, size_t file_array_size)
{
	char	new_line;
	size_t	line_len;

	line_len = ft_strlen(line);
	if (line_len == 1)

		



}

// Function to manage the wildcards in a dynamicallly allocated array of strings
// Returns a pointer to the new array or NULL if it fails
void	manage_wildcards(char **args)
{
	char	**file_array;
	size_t	file_array_size;
	int		i;

	if (!args)
	{
		shell_error_msg("manage_asterisk", "invalid arg");
		return ;
	}
	file_array = get_files_in_current_dir(".");
	if (!file_array)
		return ;
	file_array_size = count_env_size(file_array);
	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '*'))
			replace_a_line(args[i], args, file_array, file_array_size);
		i++;
	}
}

// *			Remplace 0 ou plusieurs caractères
// *.txt		Tous les fichiers se terminant par .txt
// file*		Tous les fichiers commençant par file
// *file*		Tous les fichiers contenant file
// *.*			Tous les fichiers ayant une extension