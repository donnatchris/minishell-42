#include "../../include/minishell.h"

void	echo_cmd(char **args, char **envp)
{
	int		newline;
	int		i;

	(void)envp;
	newline = 0;
	i = 0;
	while (newline_flag(args[i], &newline) == 0 && args[i] != NULL)
		i++;
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (newline == 0)
		ft_putchar_fd('\n', 1);
}

int	newline_flag(char *str, int *newline)
{
	int	i;

	i = 2;
	if (ft_strncmp(str, "-n", 2) != 0)
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	*newline = 1;
	return (0);
}
