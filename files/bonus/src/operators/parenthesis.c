/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <chdonnat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:48:16 by christophed       #+#    #+#             */
/*   Updated: 2025/03/17 15:22:18 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to free the tok->start of the dclst nodes added by manage_wildcards 
static void	delete_par_strings(t_dclst **head)
{
	t_dclst	*current;
	t_token	*tok;

	current = *head;
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
		if (current == *head)
			break ;
	}
}

// Function to run a minishell inside the minishell
// Returns the status of the last command or -1 on error
static int	mini_minishell(t_dclst **head, t_general *gen)
{
	t_tree	*tree;
	int		status;

	tree = create_tree(*head, (*head)->prev->prev);
	status = exec_tree(tree, gen);
	delete_par_strings(head);
	delete_tree(tree);
	return (status);
}

// Function to run a parenthesis node
// Returns 0 on success, -1 on error
int	run_parenthesis(t_tree *tree, t_general *gen)
{
	int		status;
	pid_t	pid;
	t_dclst	**head;

	if (!tree || !gen)
		return (shell_err_msg("run_parenthesis", "invalid arguments"), -1);
	pid = fork();
	if (pid == -1)
		return (ft_perror("run_parenthesis", "fork failed"), -1);
	if (pid == 0)
	{
		head = tokenize(((t_token *) tree->list_node->data)->start);
		status = mini_minishell(head, gen);
		dclst_clear(head);
		delete_general(gen);
		exit(status);
	}
	if (waitpid(pid, &status, 0) == -1)
		return (ft_perror("run_parenthesis", "waitpid failed"), -1);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
