/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:02:14 by christophed       #+#    #+#             */
/*   Updated: 2025/03/09 00:32:52 by christophed      ###   ########.fr       */
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
