/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signal_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:18:15 by christophed       #+#    #+#             */
/*   Updated: 2025/03/13 22:01:04 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to initialize the signal handling
void	init_signals(void)
{
	signal(SIGINT, main_signal_handler);
	signal(EOF, main_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

// Function to handle signals while in interactive mode
void	main_signal_handler(int signum)
{
	g_signals = signum;
	if (waitpid(-1, NULL, WNOHANG) == -1)
	{
		if (signum == SIGINT)
		{
			ft_putstr_fd("\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	return ;
}
