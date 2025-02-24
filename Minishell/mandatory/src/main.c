#include "../include/minishell.h"

// Function main to launch the minishell
int	main(int ac, char **av, char **envp)
{
	t_general	*gen;

	gen = NULL;
	gen = init_gen(gen, envp, av, ac);
	while (1)
	{
		delete_cmd_line(gen);
		gen->input = readline(CYAN "MINISHELL > " RESET);
		if (gen->input)
			add_history(gen->input);
		if (!gen->input[0] || gen->input[0] == '\n')
			continue ;
		gen->head = tokenize(gen->input);
		if (check_syntax(gen->head) == -1)
			continue ;
		exec_node(*gen->head, &gen->envp, gen);
	}
	delete_general(gen);
	return (0);
}
