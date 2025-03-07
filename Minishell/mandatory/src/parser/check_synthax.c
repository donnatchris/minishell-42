/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_synthax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christophedonnat <christophedonnat@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:00:42 by christophed       #+#    #+#             */
/*   Updated: 2025/03/07 05:24:20 by christophed      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to check recursively the syntax inside a parenthesis
// Returns 0 if the syntax is correct, -1 otherwise
int	check_parenthesis(t_dclst *node, t_general *gen)
{
	t_dclst	**head;
	char	*line;
	int		res;

	line = ft_strdup(((t_token *) node->data)->start);
	if (!line)
		return (ft_perror("check_parenthesis", "ft_strdup failed"));
	head = tokenize(line);
	if (!head)
	{
		free(line);
		return (shell_err_msg("check_parenthesis", "tokenize failed"));
	}
	res = check_syntax(head, gen, IN_PARENTHESIS);
	dclst_clear(head);
	free(line);
	return (res);
}

// Function to append the input line with a new line
// Returns 0 on success, -1 on error
int	append_input(t_general *gen, t_dclst *node)
{
	char	*line;
	char	*join;

	if (!gen || !gen->input_cpy || !node)
		return (shell_err_msg("append_input", "invalid arguments"));
	line = readline(CYAN "> " RESET);
	if (!line || !line[0] || line[0] == '\n')
		return (print_token_error((t_token *) node->next->data));
	join = ft_strjoin(gen->input_cpy, line);
	if (!join)
		return (ft_perror("append_input", "malloc failed"));
	delete_cmd_line(gen);
	gen->input = join;
	add_history(gen->input);
	gen->input_cpy = ft_strdup(gen->input);
	if (!gen->input_cpy)
		return (ft_perror("append_input", "ft_strdup failed"));
	gen->head = tokenize(gen->input);
	if (!gen->head)
		return (-1);
	return (check_syntax(gen->head, gen, NO_PARENTHESIS));
}

// Function to check syntax around an operator token
// Returns 0 if the syntax is correct, -1 otherwise
int	check_operator(t_dclst *node, int mode)
{
	t_token	*token;

	token = (t_token *) node->data;
	if (!is_text(node->prev) && !is_parenthesis(node->prev))
		return (print_token_error(token));
	if (is_eof(node->next))
	{
		if (mode == IN_PARENTHESIS)
			return (print_token_error(token));
		return (1);
	}
	return (0);
}

int	check_nodes(t_dclst *current, t_general *gen, int mode)
{
	while (1)
	{
		if (is_logical_operator(current) || is_pipe(current))
		{
			if (check_operator(current, mode) == -1)
				return (-1);
			if (check_operator(current, mode) == 1)
				return (append_input(gen, current));
		}
		if (is_redir(current))
			if (!is_text(current->next))
				return (print_token_error((t_token *) current->data));
		if (is_parenthesis(current))
		{
			if (!is_eof(current->prev) && !is_logical_operator(current->prev)
				&& !is_pipe(current->prev))
				return (print_token_error((t_token *) current->data));
			if (check_parenthesis(current, gen) == -1)
				return (-1);
		}
		current = current->next;
		if (is_eof(current))
			return (0);
	}
}

// Function to check the syntax of tokens in the doubly circular linked list
// Returns 0 if the syntax is correct, -1 otherwise
int	check_syntax(t_dclst **head, t_general *gen, int mode)
{
	t_dclst	*current;

	if (!head || !*head)
		return (-1);
	current = *head;
	return (check_nodes(current, gen, mode));
}
