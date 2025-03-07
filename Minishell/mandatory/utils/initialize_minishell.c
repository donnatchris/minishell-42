/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_minishell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:23:08 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 06:23:10 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Function to initialize the home value in the general structure
void	init_home_gen(t_general *gen)
{
	char	*home;

	home = ft_getenv("HOME", gen->envp);
	if (home)
	{
		gen->home = ft_strdup(home);
		if (!gen->home)
			shell_err_msg("init_home_gen", "ft_strdup failed");
	}
}

// Function to store the initial working directory in the general structure
void	init_gen_pwd(t_general *gen)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, sizeof(pwd)))
	{
		shell_err_msg("init_gen_pwd", "getcwd failed");
		delete_general(gen);
		exit(1);
	}
	gen->pwd = ft_strdup(pwd);
	if (!gen->pwd)
	{
		shell_err_msg("init_gen_pwd", "ft_strdup failed");
		delete_general(gen);
		exit(1);
	}
}

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
		return (shell_err_msg("change_shlvl", "ft_itoa failed"), -1);
	update_env_var("SHLVL", '=', new_shlvl, envp);
	free(new_shlvl);
	return (0);
}

// Function to initilaize the minishell
// Returns a pointer to the general structure or NULL if it fails
t_general	*init_gen(t_general *gen, char **envp, char **av, int ac)
{
	(void)ac;
	(void)av;
	gen = (t_general *) malloc(sizeof(t_general));
	if (!gen)
	{
		shell_err_msg("main", "malloc failed");
		exit (1);
	}
	ft_memset(gen, 0, sizeof(t_general));
	gen->envp = copy_env(envp);
	if (!gen->envp)
	{
		shell_err_msg("init_minishell", "failed to copy envp");
		delete_general(gen);
		exit(1);
	}
	if (change_shlvl(&gen->envp) == -1)
	{
		delete_general(gen);
		exit(1);
	}
	init_gen_pwd(gen);
	init_home_gen(gen);
	return (gen);
}
