/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:02:14 by christophed       #+#    #+#             */
/*   Updated: 2025/03/14 15:12:00 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signals = SIGINT;
	}
}

void	heredoc_signals(void)
{
	signal(SIGINT,SIG_DFL);
	signal(EOF, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
// Function to ignore all the signals
void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(EOF, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(EOF, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
