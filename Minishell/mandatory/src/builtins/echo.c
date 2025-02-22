#include "../../include/minishell.h"

int	echo_cmd(char **args, char **envp)
{
	int		newline;
	int		i;

	(void)envp;
	if (args[0] == NULL)
		return (ft_putchar_fd('\n', 1), 0);
	newline = 0;
	i = 0;
	while (newline_flag(args[i]) == 0)
	{
		newline = 1;
		i++;
		if (args[i] == NULL)
			break ;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	newline_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (1);
	i++;
	if (str[i] != 'n')
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}
