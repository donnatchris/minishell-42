#include "../include/minishell.h"

// Function to free the command array
void	delete_str_tab(char **tab)
{
	int i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

// Function to free the data from the doubly circular linked list
// and then free the doubly circular linked list
// void	clear_dclst_data(t_dclst **head)
// {
// 	t_dclst	*current;

// 	if (!head || !*head)
// 		return ;
// 	current = *head;
// 	while (1)
// 	{
// 		if (current->data)
// 			free(current->data);
// 		current->data = NULL;
// 		current = current->next;
// 		if (current == *head)
// 			break ;
// 	}
// 	dclst_clear(head);
// }

// Function to reinitialize the command line
void	delete_cmd_line(t_general *gen)
{
	if (!gen)
		return ;
	if (gen->input)
		free(gen->input);
	if (gen->head)
		dclst_clear(gen->head);
	gen->input = NULL;
	gen->head = NULL;
}

// Function to delete the general structure
void	delete_general(t_general *gen)
{
	if (!gen)
		return ;
	delete_cmd_line(gen);
	if (gen->envp)
		delete_str_tab(gen->envp);
	free(gen);
}