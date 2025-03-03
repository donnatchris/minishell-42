#include "../../include/minishell.h"

static int	argslen(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}
void	exit_cmd(char **args, char **envp, t_general *gen)
{
	long	exit_status;
	char	*endptr;

	(void)envp;
	ft_putstr_fd("exit\n", 1);
	if (!args[1])
	{
		delete_general(gen);
		exit(0);
	}
	exit_status = ft_strtol(args[1], &endptr, 10);
	if (*endptr != '\0' || errno == ERANGE)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		delete_general(gen);
		exit(2);
	}
	if (argslen(args) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	delete_general(gen);
	exit((exit_status) % 256);
}
// changed every args[0] to args[1] in the exit function
// and if (argslen(args) > 1) to if (argslen(args) > 2)