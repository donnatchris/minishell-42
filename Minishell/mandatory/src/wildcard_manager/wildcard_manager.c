#include "../../include/minishell.h"

char	**replace_one_arg(char *arg, char **args, char **file_array, size_t size)
{
	size_t	i;
	char	*ptr1;
	char	*ptr2;
	char	**new_args;

	ptr1 = ft_strchr(arg, '*');
	ptr2 = ft_strrchr(arg, '*');
	if (ptr1 && ptr2 && ptr1 == ptr2)
		ptr2 = NULL;
	new_args = (char *) malloc(sizeof(char *) * 1);
	if (new_args)
		return (ft_perror("replace_one_arg", "malloc failed"));
	new_args[0] = NULL;
	i = 0;
	while (file_array[i])
	{
		manage_file_line(arg, file_array[i], ptr1, ptr2);
		i++;
	}
}

void	manage_one_arg(char *arg, char **args)
{
	int		mode;
	char	**file_array;
	size_t	file_array_size;

	if (arg[0] == '.')
		mode = W_HIDDEN;
	else
		mode = NO_HIDDEN;
	file_array = get_files_in_dir(".", mode);
	if (!file_array)
		return ;
	file_array_size = count_env_size(file_array);
	replace_one_arg(arg, args, file_array, file_array_size);
	delete_str_tab(file_array);
}

// Function to manage the wildcards in a dynamicallly allocated array of strings
void	manage_wildcards(char **args)
{

	int		i;

	if (!args)
	{
		shell_error_msg("manage_asterisk", "invalid arg");
		return ;
	}
	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '*'))
			manage_one_arg(args[i], args);
		i++;
	}
}

// *			Remplace 0 ou plusieurs caractères
// *.txt		Tous les fichiers se terminant par .txt
// file*		Tous les fichiers commençant par file
// *file*		Tous les fichiers contenant file
// *.*			Tous les fichiers ayant une extension