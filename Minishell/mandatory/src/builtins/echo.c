/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:54:12 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 04:55:58 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to check if the argument is a newline flag
// Returns 0 if the argument is a newline flag, 1 otherwise
static int	newline_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (1);
	i++;
	if (str[i] != 'n')
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

// Function to print the arguments (like the echo command)
// Returns 0 on success or -1 on error
int	echo_cmd(char **args, char **envp)
{
	int		newline;
	int		i;

	(void)envp;
	if (args[1] == NULL)
		return (ft_putchar_fd('\n', 1), 0);
	newline = 0;
	i = 1;
	while (newline_flag(args[i]) == 0)
	{
		newline = 1;
		i++;
		if (args[i] == NULL)
			break ;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
