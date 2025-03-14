/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:57:28 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 05:24:20 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to print the actual working directory
// like the pwd comand in bash
// Returns 0 on success, -1 on failure
int	pwd_cmd(char **args, char **envp)
{
	char	current_dir[PATH_MAX];

	(void)args;
	(void)envp;
	if (!getcwd(current_dir, sizeof(current_dir)))
		return (shell_err_msg("pwd", "getcwd failed"));
	else
		ft_printf("%s\n", current_dir);
	return (0);
}
