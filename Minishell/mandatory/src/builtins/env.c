/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:57:51 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 05:24:20 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to print the environment variables
// like the env command in bash
int	env_cmd(char **args, char **envp)
{
	int	i;

	(void)args;
	if (!envp)
		return (shell_err_msg("env", "invalid arguments"));
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strchr(envp[i], '='))
		{
			ft_putstr_fd(envp[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return (0);
}
