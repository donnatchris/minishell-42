#include "../include/minishell.h"

// Global variable for handling signals
int	g_signals;

// Function main to launch the minishell
int	main(int ac, char **av, char **envp)
{
	t_general	*gen;

	gen = NULL;
	gen = init_gen(gen, envp, av, ac);
	signal(SIGINT, signal_handler);
	signal(EOF, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (g_signals != EOF)
	{
		g_signals = 0;
		delete_cmd_line(gen);
		gen->input = readline(CYAN "MINISHELL > " RESET);
		if (!gen->input)
			break ;
		if (gen->input)
			add_history(gen->input);
		if (!gen->input[0] || gen->input[0] == '\n')
			continue ;
		gen->head = tokenize(gen->input);
		if (check_syntax(gen->head) == -1)
			continue ;
		gen->tree = create_tree(*gen->head, (*gen->head)->prev->prev);

		// to test a line of command without any operator:
		// exec_node(*gen->head, &gen->envp, gen);

		// to see the created tokens:
		ft_printf("\nPrinting tokens:\n");
		print_dclst_tokens(gen->head);

		// to see the created tree:
		ft_printf("\nPrinting tree:\n");
		print_tree(gen->tree);

		// to test the tree execution:
		exec_tree(gen->tree, &gen->envp, gen);
	}
	delete_general(gen);
	return (0);
}
