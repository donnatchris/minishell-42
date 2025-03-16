/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:31:29 by christophed       #+#    #+#             */
/*   Updated: 2025/03/15 21:22:49 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to add an argument to the current argument
// Returns the new argument or NULL if it fails
static char	*concat_arg(char *arg, t_dclst *node, t_general *gen)
{
	char	*next_arg;
	char	*temp;

	next_arg = manage_dollar((t_token *) node->data, gen);
	if (!next_arg)
		return (shell_err_msg("add_arg", "malloc failed"), NULL);
	temp = arg;
	arg = ft_strjoin(arg, next_arg);
	if (!arg)
		shell_err_msg("add_arg", "malloc failed");
	free(temp);
	free(next_arg);
	return (arg);
}

// Function to expand the array of arguments
// Returns the new array of arguments (and increments the index)
// or NULL if it fails
static char	**expand_array(char **args, char *arg, int *i)
{
	args = ft_realloc_str_array(args, *i + 2);
	args[*i] = arg;
	(*i)++;
	if (!args)
		shell_err_msg("expand_array", "malloc failed");
	else
		args[*i] = NULL;
	return (args);
}

// Function to find the next argument
// Returns the node found or NULL if there is no more argument
static t_dclst	*find_next_arg(t_dclst *node)
{
	t_dclst	*find;
	
	while(!is_tree_branch(node) && !is_eof(node))
	{
		if (is_text(node))
		{
			if (!is_redir(node->prev))
			{
				if (has_space(node->prev) || !is_text(node->prev)) // modif recente (ajout !is_text)
					return (node);
				find = node->prev;
				while (is_text(find) && !has_space(find))
					find = find->prev;
				if (!is_redir(find))
				{
					if (is_redir(find->prev))
						return (node);
				}
			}
		}
		node = node->next;		
	}
	return (NULL);
}

// Function to create an array of arguments after a dclst node
// Returns the array of arguments
// RETURN MUST BE FREED AFTER USE
char	**extract_args(t_dclst *node, t_general *gen)
{
	char	*arg;
	char	**args;
	int		i;
	args = ft_realloc_str_array(NULL, 1);
	if (!args)
		return (shell_err_msg("extract args", "malloc failed"), NULL);
	node = find_next_arg(node);
	if (!node)
		return(shell_err_msg("extract args", "invalid arguments"), NULL);
	i = 0;
	while (node)
	{
		arg = manage_dollar((t_token *) node->data, gen);
		while (!has_space(node) && is_text(node->next))
		{
			arg = concat_arg(arg, node->next, gen);
			if (!arg)
				return (NULL);
			if (!has_space(node->next) && is_text(node->next->next))
				node = node->next;
			else
				break ;
		}
		arg = manage_wildcards(arg, node, gen);
		args = expand_array(args, arg, &i);
		node = find_next_arg(node->next);
	}
	return (args);
}
