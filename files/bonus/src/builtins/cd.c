/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:57:09 by christophed       #+#    #+#             */
/*   Updated: 2025/03/15 21:28:44 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to go the actual dir
// Returns a pointer to the path
// Returns NULL on failure
static char	*find_actual_dir(void)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, sizeof(pwd)))
		return (shell_err_msg("cd", "getcwd failed"), NULL);
	return (ft_strdup(pwd));
}

// Function to update or create PWD and OLDPWD in the environment variables
// Returns 0 on success, -1 on failure
static void	actualize_cd_env(char *old, char ***envp, t_general *gen, char *pwd)
{
	if (update_env_var("OLDPWD", '=', old, envp) == -1)
		shell_err_msg("cd", "failed to create OLDPWD");
	if (update_env_var("PWD", '=', pwd, envp) == -1)
		shell_err_msg("cd", "failed to create PWD");
	if (gen->pwd)
		free(gen->pwd);
	gen->pwd = find_actual_dir();
}

// Function to find the path for the cd command
// Returns a pointer to the path
// Returns NULL on failure
static char	*find_cd_path(char *input, char **envp, char *home, char *old)
{
	if ((!input || *input == '\0') && !home)
		return (shell_err_msg("cd", "HOME not set"), NULL);
	if (!input || *input == '\0')
		input = home;
	if (!ft_strncmp(input, "-", 1) && ft_strlen(input) == 1)
	{
		if (!old)
			return (shell_err_msg("cd", "OLDPWD not set"), NULL);
		else
			return (ft_strdup(ft_getenv("OLDPWD", envp)));
	}
	else
		return (ft_strdup(input));
}

// Function to change working directory like the cd command in bash
// and properly update the environment variables
// Returns 0 on success, -1 on failure
int	cd_cmd(char **args, char ***envp, t_general *gen)
{
	char	*new_pwd;
	char	*path;
	char	*old;

	if (!args || !envp || !args[0])
		return (shell_err_msg("cd", "invalid arguments"));
	old = ft_getenv("OLDPWD", *envp);
	path = args[1];
	new_pwd = find_cd_path(path, *envp, ft_getenv("HOME", *envp), old);
	if (!new_pwd)
		return (-1);
	if (chdir(new_pwd) == -1)
		return (free(new_pwd), ft_perror("cd", args[1]));
	free(new_pwd);
	new_pwd = find_actual_dir();
	actualize_cd_env(gen->pwd, envp, gen, new_pwd);
	if (new_pwd)
		free(new_pwd);
	if (args[1] && args[1][0] == '-' && args[1][1] == '\0')
		ft_printf("%s\n", ft_getenv("PWD", *envp));
	return (0);
}
