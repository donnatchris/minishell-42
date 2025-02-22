#include "../../include/minishell.h"

// Function to print the actual working directory
// like the pwd comand in bash
void	pwd_cmd(char **args, char **envp)
{
	char	current_dir[PATH_MAX];

	(void)args;
	(void)envp;
	if (!getcwd(current_dir, sizeof(current_dir)))
		shell_error_msg("pwd", "getcwd failed");
	else
		ft_printf("%s\n", current_dir);
}
