#include "../../include/minishell.h"

/*****************************************************************************
COMPILE WITH:
gcc -o parser_main_for_test -Wall -Werror -Wextra parser_main_for_test.c get_token.c tokenizer.c check_token_list.c binary_tree.c ../../../dclst/dclst1.c ../../../dclst/dclst2.c ../../../dclst/dclst3.c ../../utils/dollar_manager.c ../env/read_env.c ../builtins/echo.c -lreadline -L../../../libft -lft_inc -I../../../libft/headers/libft_H 
*****************************************************************************/

// Function to print a string from one pointer to another
void	print_string(char *start, char *end)
{
	while (start != end)
	{
		ft_printf("%c", *start);
		start++;
	}
	ft_printf("\n");
}

// Function to print priorities
void	print_priorities(t_dclst **head)
{
	t_dclst	*current;
	t_token	*token;

	if (!head || !*head)
	{
		ft_printf("No tokens to print\n");
		return ;
	}
	current = *head;
	while (1)
	{
		token = (t_token *) current->data;
		ft_printf("priority: %d\n", token->priority);
		current = current->next;
		if (current == *head)
			break ;
	}
}

// Function to print a token
void	print_a_token(t_token *token)
{
	if (!token)
	{
		ft_printf("No tokens to print\n");
		return ;
	}
	if (token->type == TOKEN_WORD)
		ft_printf("TOKEN_WORD: ");
	else if (token->type == TOKEN_PIPE)
		ft_printf("TOKEN_PIPE: ");
	else if (token->type == TOKEN_REDIR_IN)
		ft_printf("TOKEN_REDIR_IN: ");
	else if (token->type == TOKEN_REDIR_OUT)
		ft_printf("TOKEN_REDIR_OUT: ");
	else if (token->type == TOKEN_HEREDOC)
		ft_printf("TOKEN_HEREDOC: ");
	else if (token->type == TOKEN_APPEND)
		ft_printf("TOKEN_APPEND: ");
	else if (token->type == TOKEN_AND)
		ft_printf("TOKEN_AND: ");
	else if (token->type == TOKEN_OR)
		ft_printf("TOKEN_OR: ");
	else if (token->type == TOKEN_SEMICOLON)
		ft_printf("TOKEN_SEMICOLON: ");
	else if (token->type == TOKEN_STRING)
		ft_printf("TOKEN_STRING: ");
	else if (token->type == TOKEN_LITTERAL)
		ft_printf("TOKEN_LITTERAL: ");
	else if (token->type == TOKEN_PARENTHESIS)
		ft_printf("TOKEN_PARENTHESIS: ");
	else if (token->type == TOKEN_EOF)
		ft_printf("TOKEN_EOF: ");
	else if (token->type == TOKEN_ERROR)
		ft_printf("TOKEN_ERROR: ");
	// print_string(token->start, token->end);
	ft_printf("%s\n", token->start);
	// printf("avec printf: %s /priority %d\n", token->start, token->priority);
	}

// Function to print the doubly circular linked list of tokens
void	print_dclst_tokens(t_dclst **head)
{
	t_dclst	*current;
	t_token	*token;

	if (!head || !*head)
	{
		ft_printf("No list to print\n");
		return ;
	}
	current = *head;
	while (1)
	{
		token = (t_token *) current->data;
		print_a_token(token);
		current = current->next;
		if (current == *head)
			break ;
	}
}

// Main function to test with readline and echo
// int	main(int ac, char **av, char **envp)
// {
// 	t_dclst	**head;
// 	t_tree	*tree;
// 	char	*input;

// 	(void)ac;
// 	(void)av;
// 	head = NULL;
// 	while (1)
// 	{
// 		input = readline("MINISHELL: test echo > ");
// 		if (!input)
// 			return (ft_printf("\n"), 0);
// 		head = tokenize(input);
// 		if (check_syntax(head) == -1)
// 			return (clear_dclst_data(head), 1);
// 		ft_printf("\nLIST CREATED:\n");
// 		print_dclst_tokens(head);
// 		tree = create_tree(*head, (*head)->prev->prev);
// 		ft_printf("\nTREE CREATED:\n");
// 		print_tree(tree);
// 		ft_printf("\nECHO COMMAND:\n");
// 		echo_cmd(*head, (*head)->prev->prev, envp);
// 		clear_tree(tree);
// 		clear_dclst_data(head);
// 		free(input);
// 	}
// 	return (0);
// }

// Main function to test the tokenizer
// int	main(int ac, char **av, char **envp)
// {
// 	t_dclst	**head;
// 	t_tree	*tree;

// 	if (ac != 2)
// 		return (ft_printf("One argument needed\n"), 1);
// 	head = NULL;
// 	head = tokenize(av[1]);
// 	if (check_syntax(head) == -1)
// 		return (clear_dclst_data(head), 1);
// 	ft_printf("\nLIST CREATED:\n");
// 	print_dclst_tokens(head);
// 	tree = create_tree(*head, (*head)->prev->prev);
// 	ft_printf("\nTREE CREATED:\n");
// 	print_tree(tree);
// 	ft_printf("\nECHO COMMAND:\n");
// 	echo_cmd(*head, (*head)->prev->prev, envp);
// 	clear_tree(tree);
// 	clear_dclst_data(head);
// 	return (0);
// }
