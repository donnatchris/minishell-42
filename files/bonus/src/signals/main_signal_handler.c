/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signal_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:18:15 by christophed       #+#    #+#             */
/*   Updated: 2025/03/16 17:25:14 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to initialize the signal handling
void	init_signals(void)
{
	g_signals = 0;
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
			ft_printf("\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	return ;
}

// Function to handle signals while in heredoc mode
void	heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(EOF, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
