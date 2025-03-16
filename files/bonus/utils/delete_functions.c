/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:23:42 by christophed       #+#    #+#             */
/*   Updated: 2025/03/15 20:58:05 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Function to free the command array
void	delete_str_tab(char **tab)
{
	int	i;

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

// Function to free the tok->start of the dclst nodes added by manage_wildcards 
static void	delete_strings(t_general *gen)
{
	t_dclst	*current;
	t_token	*tok;

	current = *gen->head;
	while (1)
	{
		tok = (t_token *) current->data;
		if (tok->str_is_malloc)
		{
			free(tok->start);
			tok->start = NULL;
			tok->str_is_malloc = 0;
		}
		current = current->next;
		if (current == *gen->head)
			break;
	}
}

// Function to reinitialize the command line
void	delete_cmd_line(t_general *gen)
{
	if (gen->stdin_backup)
		close(gen->stdin_backup);
	if (gen->stdout_backup)
		close(gen->stdout_backup);
	if (!gen)
		return ;
	if (gen->input)
		free(gen->input);
	if (gen->input_cpy)
		free(gen->input_cpy);
	if (gen->head)
	{
		delete_strings(gen);
		dclst_clear(gen->head);
	}
	if (gen->tree)
		delete_tree(gen->tree);
	gen->input = NULL;
	gen->input_cpy = NULL;
	gen->head = NULL;
	gen->tree = NULL;
}

// Function to free the general structure
void	delete_general(t_general *gen)
{
	rl_clear_history();
	if (!gen)
		return ;
	if (gen->envp)
		delete_str_tab(gen->envp);
	if (gen->pwd)
		free(gen->pwd);
	if (gen->home)
		free(gen->home);
	delete_cmd_line(gen);
	gen->envp = NULL;
	gen->pwd = NULL;
	gen->home = NULL;
	free(gen);
	gen = NULL;
}

// Function to free everything before closing
void	delete_before_close(t_general *gen)
{
	rl_clear_history();
	unlink(TEMP_FILE);
	delete_general(gen);
}