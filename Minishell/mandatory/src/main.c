#include "../include/minishell.h"

// Main function to launch the minishell
int	main(int ac, char **av, char **envp)
{
	t_dclst	**head;
	t_tree	*tree;
	char	*input;
	char	pwd[PATH_MAX];

	(void)ac;
	(void)av;
	head = NULL;
	while (1)
	{
		ft_printf(YELLOW "%s\n" RESET, getcwd(pwd, sizeof(pwd)));
		input = readline(CYAN "MINISHELL > " RESET);
		if (!input)
			return (ft_printf("\n"), 0);
		add_history(input);

		// head = tokenize(input);
		// if (check_syntax(head) == -1)
		// 	return (clear_dclst_data(head), 1);
		// ft_printf("\nLIST CREATED:\n");
		// print_dclst_tokens(head);
		// tree = create_tree(*head, (*head)->prev->prev);
		// ft_printf("\nTREE CREATED:\n");
		// print_tree(tree);

	//	// A DECOMMENTER POUR TESTEER ECHO
		(void)tree;
		(void)head;
		ft_printf("\nECHO COMMAND:\n");
		echo_cmd(ft_split(input, ' '), envp);

	//	// A DECOMMENTER POUR TESTEER ENV
		// ft_printf("\nENV COMMAND\n");
		// char	**new_envp;
		// new_envp = copy_env(envp);
		// if (!new_envp)
		// 	return (perror("copy_env malloc failed"), 1);
		// env_cmd(&input, new_envp);
		// delete_env(new_envp);

	//	// A DECOMMENTER POUR TESTEER PWD
		// ft_printf("\nPWD COMMAND:\n");
		// pwd_cmd(&input, envp);

	//	// A DECOMMENTER POUR TESTER CD
		// ft_printf("\nCD COMMAND\n");
		// char	**new_envp;
		// new_envp = copy_env(envp);
		// if (!new_envp)
		// 	return (perror("copy_env malloc failed"), 1);
		// cd_cmd(&input, new_envp);
		// ft_printf("PWD = %s\n", ft_getenv("PWD", new_envp));
		// ft_printf("OLDPWD = %s\n", ft_getenv("OLDPWD", new_envp));
		// delete_env(new_envp);

		// clear_tree(tree);
		// clear_dclst_data(head);
		free(input);
	}
	return (0);
}