#include "../../include/minishell.h"

static int	argslen(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}
void	exit_cmd(char **args, char **envp)
{
	long	exit_status;
	char	*endptr;

	(void)envp;
	ft_putstr_fd("exit\n", 1);
	if (!args[0])
		exit(0);
	exit_status = strtol(args[0], &endptr, 10);
	if (*endptr != '\0' || errno == ERANGE)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		// delete_all();
		exit(255);
	}
	if (argslen(args) > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments", 2);
		return ;
	}
	// delete_all();
	exit((exit_status) % 256);
}
