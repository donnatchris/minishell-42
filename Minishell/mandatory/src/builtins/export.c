#include "../../include/minishell.h"

// Function to find the lowest variable in the environment (alphabetically)
// above the variable passed as an argument
// Returns the address of the variable in the environment or NULL if not found
char	*find_next_lowest_var(char *var, char **envp)
{
	int		i;
	char	*temp;

	if (!envp)
		return (NULL);
	i = 0;
	if (!var)
		var = "";
	temp = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(envp[i])) > 0 && (!temp || ft_strncmp(envp[i], temp, ft_strlen(envp[i])) < 0))
			temp = envp[i];
		i++;
	}
	return (temp);
}

// Function to print characters of a string from pointer start to pointer end
void	print_chars(char *start, char *end)
{
	while (start < end)
	{
		ft_putchar_fd(*start, 1);
		start++;
	}
}

// Function to print all the variables in the environment
// sorted alphabetically
int	print_exp_var_env(char **envp)
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

// Function to print error message of export_cmd
// Returns -1
void	print_export_error(char *arg)
{
	ft_putstr_fd("export : `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

// Function to check is the string is a valid variable name
// Return 1 if the string is valid, 0 if not
int	is_valid_var_name(char *str)
{
	if (!str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

// Function to export variables and store them in the envp
// or update the value of an existing variable
// or print the value of existing variables in the envp
// or print an error message if the variable name is invalid
// like the export command in bash
// Returns 0 on success, -1 on failure
int export_cmd(char **args, char ***envp)
{
	int		i;
	char	*value;

	if (!envp)
		return (ft_putstr_fd("export_cmd: envp not set\n", 2), -1);	
	if (!args || !*args)
		return (print_exp_var_env(*envp), 0);
	i = 0;
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
			print_export_error(args[i]);
		else
		{
			value = ft_strchr(args[i], '=');
			if (!value)
				update_env_var(args[i], ' ', NULL, envp);
			else if (*(value + 1) == '\0')
				update_env_var(args[i], '=', NULL, envp);
			else
				update_env_var(args[i], '=', value + 1, envp);
		}
		args++;
	}
	return (0);
}
