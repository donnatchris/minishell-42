#include "../../include/minishell.h"

// Function to add an argument to the current argument
// Returns the new argument or NULL if it fails
static char	*concat_arg(char *arg, t_dclst *node, char **envp, t_general *gen)
{
	char	*next_arg;
	char	*temp;

	next_arg = manage_dollar((t_token *) node->data, envp, gen->exit_status);
	if (!next_arg)
		return (shell_error_msg("add_arg", "malloc failed"), NULL);
	temp = arg;
	arg = ft_strjoin(arg, next_arg);
	if (!arg)
		shell_error_msg("add_arg", "malloc failed");
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
		shell_error_msg("expand_array", "malloc failed");
	else
		args[*i] = NULL;
	return (args);
}

// Function to find the next node that is not a redirection
// Returns the next node that is not a redirection
static t_dclst	*find_next_node(t_dclst *node)
{
	node = node->next;
	while (is_redir(node))
		node = node->next->next;
	return (node);
}

// Function to create an array of arguments after a dclst node
// Returns the array of arguments
// RETURN MUST BE FREED AFTER USE
char	**extract_args(t_dclst *node, char **envp, t_general *gen)
{
	char	*arg;
	char	**args;
	int		i;

	args = ft_realloc_str_array(NULL, 1);
	if (!args)
		return (shell_error_msg("extract args", "malloc failed"), NULL);
	i = 0;
	while (is_text(node))
	{
		arg = manage_dollar((t_token *) node->data, envp, gen->exit_status);
		arg = manage_wildcards(arg, node, gen); // line to remove if not using wildcards
		while (!has_space(node) && is_text(node->next))
		{
			arg = concat_arg(arg, node->next, envp, gen);
			if (!arg)
				return (NULL);
			node = node->next;
		}
		args = expand_array(args, arg, &i);
		node = find_next_node(node);
		if (!is_text(node) || !args)
			break ;
	}
	return (args);
}

// PREVIOUS VERSION
// char	**extract_args(t_dclst *node, char **envp, t_general *gen)
// {
// 	t_dclst	*current_node;
// 	t_dclst	*next_node;
// 	t_token	*tok;
// 	t_token	*next_tok;
// 	char	*arg;
// 	char	*temp;
// 	char	*next_arg;
// 	char	**args;
// 	int		i;

// 	args = ft_realloc_str_array(NULL, 1);
// 	if (!args)
// 		return (shell_error_msg("extract args", "malloc failed"), NULL);
// 	current_node = node;
// 	next_node = current_node->next;
// 	args[0] = NULL;
// 	tok = (t_token *) current_node->data;
// 	next_tok = (t_token *) next_node->data;
// 	i = 0;
// 	while (tok->priority == 6)
// 	{
// 		arg = manage_dollar(tok, envp, gen->exit_status);
// 		while (!tok->space && next_tok->priority == 6)
// 		{
// 			next_arg = manage_dollar(next_tok, envp, gen->exit_status);
// 			temp = arg;
// 			arg = ft_strjoin(arg, next_arg);
// 			free(temp);
// 			free(next_arg);
// 			current_node = current_node->next;
// 			next_node = next_node->next;
// 			tok = (t_token *) current_node->data;
// 			next_tok = (t_token *) next_node->data;
// 		}
// 		args = ft_realloc_str_array(args, i + 2);
// 		args[i] = arg;
// 		current_node = current_node->next;
// 		tok = (t_token *) current_node->data;
// 		while (is_redir(current_node))
// 		{
// 			current_node = current_node->next->next;
// 			tok = (t_token *) current_node->data;
// 		}
// 		next_node = current_node->next;
// 		next_tok = (t_token *) next_node->data;
// 		i++;
// 		if (tok->priority != 6 || current_node == node)
// 			break ;
// 	}
// 	args[i] = NULL;
// 	return (args);
// }