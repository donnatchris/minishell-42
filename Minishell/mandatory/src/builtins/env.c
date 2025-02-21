#include "../../include/minishell.h"

// Function to print the environment variables
// like the env command in bash
void	env_cmd(char **args, char **envp)
{
	int	i;

	(void)args;
	if (!envp)
	{
		ft_putstr_fd("env_cmd: invalid arguments\n", 2);
		return ;
	}
	i = 0;
	while (envp[i] != NULL)
	{
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}
