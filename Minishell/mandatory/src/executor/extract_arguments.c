#include "../../include/minishell.h"

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
		tok = (t_token *) current_node->data;
		while (tok->priority == 4)
		{
			current_node = current_node->next->next;
			tok = (t_token *) current_node->data;
		}
		next_node = current_node->next->next;
		next_tok = (t_token *) next_node->data;
		i++;
		if (tok->priority != 6 || current_node == node)
			break ;
	}
	args[i] = NULL;
	return (args);
	// Attention: si le noeud suivant est priority == 4,
	// il faut le skip et skip le noeud suivant aussi
	// et continuer à lire les arguments
	// jusqu'à ce qu'on tombe sur un noeud priority != 6
	// ou qu'on revienne au noeud de départ
}
