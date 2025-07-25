/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_minishell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:23:08 by christophed       #+#    #+#             */
/*   Updated: 2025/03/17 17:30:50 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Function to initialize the home value in the general structure
// (if there is no HOME variable, the home value is set to
// the current working directory)
static void	init_home(t_general *gen)
{
	char	*home;

	home = ft_getenv("HOME", gen->envp);
	if (home)
	{
		gen->home = ft_strdup(home);
		if (!gen->home)
			shell_err_msg("init_home_gen", "ft_strdup failed");
	}
	else
		gen->home = ft_strdup(gen->pwd);
}

// Function to store the initial working directory in the general structure
static void	init_pwd(t_general *gen)
{
	char	pwd[PATH_MAX];

	unset_one_env_var("OLDPWD", &gen->envp);
	if (!getcwd(pwd, sizeof(pwd)))
		shell_err_msg("init_gen_pwd", "getcwd failed");
	gen->pwd = ft_strdup(pwd);
	if (!gen->pwd)
	{
		shell_err_msg("init_gen_pwd", "ft_strdup failed");
		delete_before_close(gen);
		exit(1);
	}
}

// Function to increment the value of the SHLVL variable
// Returns 0 on success, -1 on error
static int	change_shlvl(char ***envp)
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
		return (shell_err_msg("change_shlvl", "ft_itoa failed"));
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
		shell_err_msg("init_gen", "malloc failed");
		exit (1);
	}
	ft_memset(gen, 0, sizeof(t_general));
	gen->envp = copy_env(envp);
	if (!gen->envp)
	{
		shell_err_msg("init_gen", "failed to copy envp");
		delete_general(gen);
		exit(1);
	}
	change_shlvl(&gen->envp);
	init_pwd(gen);
	init_home(gen);
	return (gen);
}
