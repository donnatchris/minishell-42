/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:01:44 by christophed       #+#    #+#             */
/*   Updated: 2025/03/10 13:34:30 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to get the length of the arguments
static int	argslen(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

// Function to print an error message when the argument is not a number
static void	eit_err_msg(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

// Function to handle the exit command
void	exit_cmd(char **args, char **envp, t_general *gen)
{
	long	exit_status;
	char	*endptr;

	(void)envp;
	ft_putstr_fd("exit\n", 1);
	if (!args[1])
	{
		delete_general(gen);
		exit(0);
	}
	exit_status = ft_strtol(args[1], &endptr, 10);
	if (*endptr != '\0' || errno == ERANGE)
	{
		eit_err_msg(args[1]);
		delete_general(gen);
		exit(2);
	}
	if (argslen(args) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	delete_general(gen);
	exit((exit_status) % 256);
}
