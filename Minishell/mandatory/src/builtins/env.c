#include "../../include/minishell.h"

void	env_cmd(char **arguments, char **envp)
{
	int	i;

	(void)arguments;
	if (!envp)
		return ;
	i = 0;
	while (envp[i] != NULL)
	{
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}
