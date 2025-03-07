/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:18:15 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 10:50:04 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to initialize the signal handling
void	init_signals(void)
{
	g_signals = 0;
	signal(SIGINT, signal_handler);
	signal(EOF, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

// Function to handle signals while in interactive mode
void	signal_handler(int signum)
{
	g_signals = signum;
	if (signum == EOF)
		ft_putstr_fd("\nexit\n", 1);
	else if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

// Function to ignore all the signals
void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(EOF, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_signals(void)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(EOF, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_signal_handler(int signum)
{
	(void) signum;
}