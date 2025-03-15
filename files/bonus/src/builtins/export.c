/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:06:07 by christophed       #+#    #+#             */
/*   Updated: 2025/03/10 16:03:23 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to find the lowest variable in the environment (alphabetically)
// above the variable passed as an argument
// Returns the address of the variable in the environment or NULL if not found
static char	*find_next_lowest_var(char *var, char **envp)
{
	int		i;
	char	*temp;

	if (!envp)
		return (NULL);
	temp = NULL;
	i = 0;
	while (envp[i])
	{
		if ((!var || compare_env_vars(envp[i], var) > 0)
			&& (!temp || compare_env_vars(envp[i], temp) < 0))
		{
			temp = envp[i];
		}
		i++;
	}
	return (temp);
}

// Function to print characters of a string from pointer start to pointer end
static void	print_chars(char *start, char *end)
{
	while (start < end)
	{
		ft_putchar_fd(*start, 1);
		start++;
	}
}

// Function to print all the variables in the environment
// sorted alphabetically
static int	print_exp_var_env(char **envp)
{
	char	*var;
	char	*eq;
	char	*value;

	if (!envp)
		return (ft_printf("\n"), -1);
	var = NULL;
	while (1)
	{
		var = find_next_lowest_var(var, envp);
		if (!var)
			break ;
		ft_printf("declare -x ");
		eq = ft_strchr(var, '=');
		if (!eq)
			ft_printf("%s\n", var);
		else
		{
			value = eq + 1;
			print_chars(var, eq);
			ft_printf("=\"%s\"", value);
			ft_printf("\n");
		}
	}
	return (0);
}

// Function to export a variable in the environment
// or update the value of an existing variable
static void	export_var(char *arg, char *name, char ***envp)
{
	char	*value;

	value = ft_strchr(arg, '=');
	if (!value)
		update_env_var(name, ' ', NULL, envp);
	else if (*(value + 1) == '\0')
		update_env_var(name, '=', NULL, envp);
	else
		update_env_var(name, '=', (value + 1), envp);
	free(name);
}

// Function to export variables and store them in the envp
// or update the value of an existing variable
// or print the value of existing variables in the envp
// or print an error message if the variable name is invalid
// like the export command in bash
// Returns 0 on success, -1 on failure
int	export_cmd(char **args, char ***envp)
{
	int		i;
	int		status;
	char	*name;

	if (!envp || !*envp || !args || !args[0])
		return (shell_err_msg("export", "invalid arguments"));
	status = 0;
	if (!args || !args[1])
		return (print_exp_var_env(*envp), status);
	i = 1;
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
			status = shell_error_quote("export", args[i]);
		else
		{
			name = cut_name(args[i]);
			if (!name)
				return (-1);
			export_var(args[i], name, envp);
		}
		args++;
	}
	return (status);
}
