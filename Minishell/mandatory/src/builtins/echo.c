#include "../../include/minishell.h"

void	echo_cmd(char **args, char **envp)
{
	int	newline_flag;
	int	argument;
	int	i;

	(void)envp;
	newline_flag = 0;
	argument = 0;
	i = 0;
	while (args[i])
	{
		if (!argument && is_newline_flag(args[i]))
			newline_flag = 1;
		else
		{
			argument = 1;
			ft_printf("%s", args[i]);
			if (args[i + 1])
				ft_printf(" ");
		}
		i++;
	}
	if (!newline_flag)
		ft_printf("\n");
}

int	is_newline_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	if (str[i] != 'n')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
