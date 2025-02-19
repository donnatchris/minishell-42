#include "../../include/minishell.h"


// Function to print the actual working directory
// like the pwd comand
void	pwd_cmd()
{
	char	current_dir[PATH_MAX];

	if (!getcwd(current_dir, sizeof(current_dir)))
		perror("pwd: error retrieving current directory");
	else
		ft_printf("%s\n", current_dir);
}
