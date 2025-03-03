#include "../../include/minishell.h"

// Function to initialize the signal handling in main
void	init_main_signals(int option)
{
	g_signals = 0;
	if (option == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(EOF, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (option == 1)
	{
		signal(SIGINT, main_signal_handler);
		signal(EOF, main_signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}

// Function to initialize the signal handling in heredoc
void	init_heredoc_signals(void)
{
	g_signals = 0;
	signal(SIGINT, heredoc_signal_handler);
	signal(EOF, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	main_signal_handler(int signum)
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

void	heredoc_signal_handler(int signum)
{
	g_signals = signum;
	if (signum == SIGINT)
		exit();
	return ;
}
