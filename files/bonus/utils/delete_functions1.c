/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_functions1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:23:42 by christophed       #+#    #+#             */
/*   Updated: 2025/03/16 14:46:00 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Function to delete a delim structure
void	delete_delim(t_delim *delim)
{
	if (!delim)
		return ;
	if (delim->str)
		free(delim->str);
	free(delim);
}

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
