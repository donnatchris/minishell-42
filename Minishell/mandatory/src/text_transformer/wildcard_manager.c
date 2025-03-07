/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:21:05 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 06:21:07 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to insert a new node in the doubly circular linked list
// Returns the new node or NULL if an error occurs
static t_dclst	*insert_new_node(t_token *token, t_dclst *anchor)
{
	t_dclst	*new_node;

	new_node = dclst_create_node(token);
	if (!new_node)
	{
		free(token->start);
		free(token);
		shell_err_msg("insert_additionnal_nodes", "dclst_create_node failed");
		return (NULL);
	}
	new_node->next = anchor->next;
	new_node->prev = anchor;
	anchor->next->prev = new_node;
	anchor->next = new_node;
	return (new_node);
}

// function to affect the values of the token
static void	affect_token_values(t_token *token, char *matching_str)
{
	token->type = TOKEN_LITTERAL;
	token->start = ft_strdup(matching_str);
	token->end = NULL;
	token->space = 1;
	token->priority = 6;
}

// Function to insert additional nodes in the doubly circular linked list
static void	insert_additional_nodes(t_dclst *node, char **matching_array)
{
	t_dclst	*current;
	t_dclst	*new_node;
	t_token	*token;
	size_t	i;

	current = node;
	i = 1;
	while (matching_array[i])
	{
		token = (t_token *) malloc(sizeof(t_token) + 1);
		if (!token)
		{
			shell_err_msg("insert_additionnal_nodes", "malloc failed");
			return ;
		}
		affect_token_values(token, matching_array[i]);
		insert_new_node(token, current);
		new_node = dclst_create_node(token);
		if (!new_node)
			return ;
		current = current->next;
		i++;
	}
}

// Function to manage the wildcards in a dynamicallly allocated array of strings
// It takes the array of strings and replaces the strings with wildcards
// with the matching filenames
// Returns the new array of strings or NULL on failure
// RETURN MUST BE FREED AFTER USE
char	*manage_wildcards(char *arg, t_dclst *node, t_general *gen)
{
	char	**file_array;
	char	**matching_array;
	char	pwd[PATH_MAX];
	int		mode;

	(void) gen;
	if (arg && arg[0] == '.')
		mode = W_HIDDEN;
	else
		mode = NO_HIDDEN;
	if (((t_token *) node->data)->type != TOKEN_WORD || !ft_strchr(arg, '*'))
		return (arg);
	file_array = get_files_in_dir(getcwd(pwd, sizeof(pwd)), mode);
	if (!file_array)
		return (arg);
	matching_array = extract_matching_filenames(arg, file_array);
	if (!matching_array)
		return (delete_str_tab(file_array), arg);
	delete_str_tab(file_array);
	insert_additional_nodes(node, matching_array);
	return (free(arg), matching_array[0]);
}
