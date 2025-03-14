/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signal_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:18:15 by christophed       #+#    #+#             */
/*   Updated: 2025/03/14 15:08:07 by chdonnat         ###   ########.fr       */
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
			ft_printf("\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	return ;
}
