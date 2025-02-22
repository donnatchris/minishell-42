#include "../include/minishell.h"

// Function to print perror message with "minishell: " prefix
void	ft_perror(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	perror(msg);
}

// Function to print an error message when execve_cmd fails
// Returns: -1
int	shell_error_msg(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}