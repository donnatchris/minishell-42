#include "../include/minishell.h"
//test
// int	run_minishell



// Main function to launch the minishell
int	main(int ac, char **av, char **envp)
{
	t_dclst	**head;
	t_tree	*tree;
	char	**new_envp;
	char	*input;

	(void)ac;
	(void)av;
	(void)tree;
	new_envp = copy_env(envp);
	if (!new_envp)
		return (shell_error_msg("main", "failed to copy envp"));
	change_shlvl(&new_envp);
	head = NULL;
	while (1)
	{
		input = readline(CYAN "MINISHELL > " RESET);
		if (!input)
			continue ;
		add_history(input);
		if (!input[0] || input[0] == '\n')
		{
			if (input)
				free(input);
			ft_printf("\n");
			continue ;
		}
		head = tokenize(input);
		if (!head)
		{
			free(input);
			continue ;
		}
		if (check_syntax(head) == -1)
		{
			clear_dclst_data(head);
			free(input);
			continue ;
		}
		exec_node(*head, &new_envp);
		// ft_printf("\nLIST CREATED:\n");
		// print_dclst_tokens(head);
		// tree = create_tree(*head, (*head)->prev->prev);
		// ft_printf("\nTREE CREATED:\n");
		// print_tree(tree);


	//	// A DECOMMENTER POUR TESTER ECHO
		// ft_printf("\nECHO COMMAND:\n");
		// echo_cmd(ft_split(input, ' '), envp);

	//	// A DECOMMENTER POUR TESTER PWD
		// ft_printf("\nPWD COMMAND:\n");
		// pwd_cmd(&input, envp);

	//	// A DECOMMENTER POUR TESTER CD
		// ft_printf("\nCD COMMAND\n");
		// cd_cmd(&input, &new_envp);
		// ft_printf("OLDPWD = %s\n", ft_getenv("OLDPWD", new_envp));
		// ft_printf("PWD = %s\n", ft_getenv("PWD", new_envp));

	//	// A DECOMMENTER POUR TESTER EXPORT
		// ft_printf("EXPORT COMMAND:\n");
		// export_cmd(ft_split(input, ' '), &new_envp);

	//	// A DECOMMENTER POUR TESTER UNSET
		// ft_printf("UNSET COMMAND:\n");
		// unset_cmd(ft_split(input, ' '), &new_envp);

	//	// A DECOMMENTER POUR TESTEER ENV
		// ft_printf("\nENV COMMAND\n");
		// env_cmd(&input, new_envp);
		
//	// A DECOMMENTER POUR TESTER EXECVE
		// ft_printf("\nEXECVE COMMAND\n");
		// execve_cmd(input, ft_split(input, ' '), new_envp);

		// ft_printf(YELLOW "%s\n" RESET, getcwd(pwd, sizeof(pwd)));
		// input = readline(CYAN "MINISHELL > " RESET);
		// if (!input)
		// 	return (ft_printf("\n"), 0);
		// add_history(input);

		// clear_tree(tree);
		// clear_dclst_data(head);
		// free(input);
		
		free(input);
	}
	delete_str_tab(new_envp);
	return (0);
}