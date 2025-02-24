#include "../include/minishell.h"

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
