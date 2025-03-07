/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:18:15 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 05:18:21 by christophed      ###   ########.fr       */
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
