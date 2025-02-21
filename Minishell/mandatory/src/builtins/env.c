#include "../../include/minishell.h"

// Function to print the environment variables
// like the env command in bash
int	env_cmd(char **args, char **envp)
{
	int	i;

	(void)args;
	if (!envp)
	{
		ft_putstr_fd("env_cmd: invalid arguments\n", 2);
		return (-1);
	}
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
