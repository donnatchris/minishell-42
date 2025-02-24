#include "../../include/minishell.h"

// Function to reallocate a string array
// Returns the new string array
// RETURN MUST BE FREED AFTER USE
char	**ft_realloc_str_array(char **tab, size_t new_size)
{
	char	**new_tab;
	size_t	i;

	if (!tab)
		return ((char **) malloc(sizeof(char *) * new_size));
	new_tab = (char **) malloc(sizeof(char *) * new_size);
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab[i] && i < new_size - 1)
	{
		new_tab[i] = tab[i];
		i++;
	}
	while (i < new_size)
	{
		new_tab[i] = NULL;
		i++;
	}
	free(tab);
	return (new_tab);
}

// Function to create an array of arguments after a dclst node
// Returns the array of arguments
// RETURN MUST BE FREED AFTER USE
char	**extract_args(t_dclst *node, char **envp)
{
	t_dclst	*current_node;
	t_dclst	*next_node;
	t_token	*tok;
	t_token	*next_tok;
	char	*arg;
	char	*temp;
	char	*next_arg;
	char	**args;
	int		i;
	args = ft_realloc_str_array(NULL, 1);
	if (!args)
		return (shell_error_msg("extract args", "malloc failed"), NULL);
	current_node = node;
	next_node = current_node->next;
	args[0] = NULL;
	tok = (t_token *) current_node->data;
	next_tok = (t_token *) next_node->data;
	i = 0;
	while (tok->priority == 6)
	{
		arg = manage_dollar(tok, envp);
		while (!tok->space && next_tok->priority == 6)
		{
			next_arg = manage_dollar(next_tok, envp);
			temp = arg;
			arg = ft_strjoin(arg, next_arg);
			free(temp);
			free(next_arg);
			current_node = current_node->next;
			next_node = next_node->next;
			tok = (t_token *) current_node->data;
			next_tok = (t_token *) next_node->data;
		}
		args = ft_realloc_str_array(args, i + 2);
		args[i] = arg;
		current_node = current_node->next;
		next_node = next_node->next;
		tok = (t_token *) current_node->data;
		next_tok = (t_token *) next_node->data;
		i++;
		if (tok->priority != 6 || current_node == node)
			break ;
	}
	args[i] = NULL;
	return (args);
}
