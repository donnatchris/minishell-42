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
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

// Function to free the binary tree
void	delete_tree(t_tree *root)
{
	if (!root)
		return ;
	if (root->left)
		delete_tree(root->left);
	if (root->right)
		delete_tree(root->right);
	free(root);
	root = NULL;
}

// Function to reinitialize the command line
void	delete_cmd_line(t_general *gen)
{
	if (!gen)
		return ;
	if (gen->input)
		free(gen->input);
	if (gen->head)
		dclst_clear(gen->head);
	if (gen->tree)
		delete_tree(gen->tree);
	gen->input = NULL;
	gen->head = NULL;
	gen->tree = NULL;
}

// Function to free the general structure
void	delete_general(t_general *gen)
{
	if (!gen)
		return ;
	delete_cmd_line(gen);
	if (gen->envp)
		delete_str_tab(gen->envp);
	free(gen);
	gen = NULL;
}
