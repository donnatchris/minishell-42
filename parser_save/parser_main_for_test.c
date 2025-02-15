#include "../../include/minishell.h"
#include "../../include/parser.h"
// #include "../../../dclst/dclst.h"

/*
COMPILE WITH:
gcc -o parser_main_for_test parser_main_for_test.c get_token.c tokenizer.c ../../../dclst/dclst1.c ../../../dclst/dclst2.c ../../../dclst/dclst3.c -L../../../libft -lft_inc -I../../../libft/headers/libft_H
*/

// Function to print each token in the doubly circular linked list
void	print_tokens(t_dclst **head)
{
	ft_printf("print_tokens:\n");
	t_dclst	*current;
	t_token	*token;

	if (!head || !*head)
		return ;
	current = *head;
	while (1)
	{
		token = (t_token *)current->data;
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
		else if (token->type == TOKEN_VAR)
			ft_printf("TOKEN_VAR: ");
		else if (token->type == TOKEN_PARENTHESIS)
			ft_printf("TOKEN_PARENTHESIS: ");
		else if (token->type == TOKEN_EOF)
			ft_printf("TOKEN_EOF: ");
		else if (token->type == TOKEN_ERROR)
			ft_printf("TOKEN_ERROR: ");
		current = current->next;
		if (current == *head)
			break ;
	}
}

// Main function to test the tokenizer
int	main(void)
{
	t_dclst	**head;

	// if (ac != 2)
	// 	return (1);
	// ft_printf("av[1]: %s\n", av[1]);
	char str[] = "salut les loulous";
	head = NULL;
	head = tokenize_to_dclst(str);
	if (!head)
		ft_printf("head est vide\n");
	print_tokens(head);
	clear_dclst_data(head);
	dclst_clear(head);
	return (0);
}