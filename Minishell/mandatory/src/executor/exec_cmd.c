/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:29:39 by christophed       #+#    #+#             */
/*   Updated: 2025/03/12 10:33:23 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to check if the command is a soft builtin
// (meaning it cannot modify the environment variables)
// Returns the function pointer to the builtin
// or NULL if it is not a hard builtin
static int	(*soft_builtin(char *cmd))(char **args, char **envp)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", 4) && len == 4)
		return (echo_cmd);
	else if (!ft_strncmp(cmd, "env", 3) && len == 3)
		return (env_cmd);
	else if (!ft_strncmp(cmd, "pwd", 3) && len == 3)
		return (pwd_cmd);
	return (NULL);
}

// Function to check if the command is a hard builtin
// (meaning it can modify the environment variables)
// Returns the function pointer to the builtin
// or NULL if it is not a hard builtin
static int	(*hard_builtin(char *cmd))(char **args, char ***envp)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "export", 6) && len == 6)
		return (export_cmd);
	else if (!ft_strncmp(cmd, "unset", 5) && len == 5)
		return (unset_cmd);
	return (NULL);
}

// Function to execute a command (other than exit or cd)
// Returns the exit status of the command
static int	exec_function(char **args, char ***envp, t_general *gen)
{
	int	status;
	int	(*hard_built_func)(char **, char ***);
	int	(*soft_built_func)(char **, char **);

	hard_built_func = hard_builtin(args[0]);
	soft_built_func = soft_builtin(args[0]);
	if (hard_built_func)
		status = hard_built_func(args, envp);
	else if (soft_built_func)
		status = soft_built_func(args, *envp);
	else
		status = execve_cmd(args[0], args, *envp, gen);
	return (status);
}

// Function to execute a command taking a node as the command
// and the followin nodes as arguments
// Returns the exit status of the command
int	exec_cmd(t_dclst *node, t_general *gen)
{
	char	**args;
	int		status;

	if (!node || !gen)
		return (0);
	status = 0;
	args = extract_args(node, gen);
	if (!args)
		return (shell_err_msg("exec_node", "extract_args failed"), -1);
	if (!ft_strncmp(args[0], "exit", 4) && ft_strlen(args[0]) == 4)
		exit_cmd(args, gen->envp, gen);
	else if (!ft_strncmp(args[0], "cd", 2) && ft_strlen(args[0]) == 2)
		status = cd_cmd(args, &gen->envp, gen);
	else
		status = exec_function(args, &gen->envp, gen);
	delete_str_tab(args);
	return (status);
}
