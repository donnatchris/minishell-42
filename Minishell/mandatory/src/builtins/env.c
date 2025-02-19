#include "../../include/minishell.h"

/*****************************************************************************
COMPILE WITH:
gcc -o test_env -Wall -Werror -Wextra env.c ../../../libft/src/libft_SRC/ft_putstr_fd.c ../../../libft/src/libft_SRC/ft_putchar_fd.c
*****************************************************************************/

void	env_cmd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

/*int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	env_cmd(envp);
	(void)envp;
	return (0);
}*/