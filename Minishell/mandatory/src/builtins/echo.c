#include "../../include/minishell.h"

void	echo_cmd(char **arguments, char **envp)
{
	int		newline;
	int		i;

	(void)envp;
	newline = 0;
	i = 0;
	while (newline_flag(arguments[i], &newline) == 0 && arguments[i] != NULL)
		i++;
	while (arguments[i] != NULL)
	{
		ft_putstr_fd(arguments[i], 1);
		if (arguments[i + 1] != NULL)
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
