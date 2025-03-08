/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:02:14 by christophed       #+#    #+#             */
/*   Updated: 2025/03/08 15:22:54 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_signal_handler(int signum)
{
	if (signum == EOF)
	{
		ft_putstr_fd("LOOOOOL", 1);
		exit(0);
	}
}

void	heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(EOF, heredoc_signal_handler);
	signal(SIGQUIT, SIG_DFL);
	
	// signal(SIGINT, heredoc_signal_handler);
	// signal(EOF, heredoc_signal_handler);
	// signal(SIGQUIT, SIG_IGN);
}
// Function to ignore all the signals
void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(EOF, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
