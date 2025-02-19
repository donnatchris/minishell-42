#include "../../include/minishell.h"

void	env_cmd(char **envp)
{
	int	i;

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
