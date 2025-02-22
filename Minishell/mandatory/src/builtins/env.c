#include "../../include/minishell.h"

// Function to print the environment variables
// like the env command in bash
int	env_cmd(char **args, char **envp)
{
	int	i;

	(void)args;
	if (!envp)
		return (shell_error_msg("env", "invalid arguments"));
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strchr(envp[i], '='))
		{
			ft_putstr_fd(envp[i], 1);
			ft_putchar_fd('\n', 1);
		}
	i++;
	}
	return (0);
}
