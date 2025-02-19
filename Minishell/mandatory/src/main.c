#include "../include/minishell.h"

// Main function to test
int	main(int ac, char **av, char **envp)
{
	t_dclst	**head;
	t_tree	*tree;
	char	*input;

	(void)ac;
	(void)av;
	head = NULL;
	while (1)
	{
		input = readline(YELLOW "MINISHELL: test echo > " RESET);
		if (!input)
			return (ft_printf("\n"), 0);
		head = tokenize(input);
		if (check_syntax(head) == -1)
			return (clear_dclst_data(head), 1);
		ft_printf("\nLIST CREATED:\n");
		print_dclst_tokens(head);
		tree = create_tree(*head, (*head)->prev->prev);
		ft_printf("\nTREE CREATED:\n");
		print_tree(tree);
		ft_printf("\nECHO COMMAND:\n");
		echo_cmd(*head, (*head)->prev->prev, envp);
		clear_tree(tree);
		clear_dclst_data(head);
		free(input);
	}
	return (0);
}