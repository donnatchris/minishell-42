#include "../include/minishell.h"

// Function to initilaize the minishell
t_general	*init_gen(t_general *gen, char **envp, char **av, int ac)
{
	(void)ac;
	(void)av;
	gen = (t_general *) malloc(sizeof(t_general));
	if (!gen)
	{
		shell_error_msg("main", "malloc failed");
		exit (1);
	}
	ft_memset(gen, 0, sizeof(t_general));
	gen->envp = copy_env(envp);
	if (!gen->envp)
	{
		shell_error_msg("init_minishell", "failed to copy envp");
		delete_general(gen);
		exit(1);
	}
	if (change_shlvl(&gen->envp) == -1)
	{
		delete_general(gen);
		exit(1);
	}
	return (gen);
}

// // Function to initilaize the minishell
// void	init_gen(t_general *gen, char **envp, char **av, int ac)
// {
// 	(void)ac;
// 	(void)av;
// 	ft_memset(gen, 0, sizeof(t_general));
// 	gen->envp = copy_env(envp);
// 	if (!gen->envp)
// 	{
// 		shell_error_msg("init_minishell", "failed to copy envp");
// 		exit(1);
// 	}
// 	if (change_shlvl(&gen->envp) == -1)
// 		exit(1);
// }

// Function to increment the value of the SHLVL variable
// Returns 0 on success, -1 on error
int	change_shlvl(char ***envp)
{
	char	*shlvl;
	char	*new_shlvl;
	int		i;

	shlvl = ft_getenv("SHLVL", *envp);
	if (!shlvl)
		i = 0;
	else
		i = ft_atoi(shlvl);
	new_shlvl = ft_itoa(i + 1);
	if (!new_shlvl)
		return (shell_error_msg("change_shlvl", "ft_itoa failed"), -1);
	update_env_var("SHLVL", '=', new_shlvl, envp);
	free(new_shlvl);
	return (0);
}
