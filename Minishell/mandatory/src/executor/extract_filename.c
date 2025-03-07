#include "../../include/minishell.h"

// Function to add an argument to the current argument
// Returns the new argument or NULL if it fails
static char	*concat_filenames(char *filename, t_dclst *node, char **envp, t_general *gen)
{
	char	*next_arg;
	char	*temp;

	next_arg = manage_dollar((t_token *) node->data, envp, gen->exit_status);
	if (!next_arg)
		return (shell_err_msg("add_arg", "malloc failed"), filename);
	temp = filename;
	filename = ft_strjoin(filename, next_arg);
	if (!filename)
		shell_err_msg("add_arg", "malloc failed");
	free(temp);
	free(next_arg);
	return (filename);
}

// Function to create an array of arguments after a dclst node
// Returns the array of arguments
// RETURN MUST BE FREED AFTER USE
char	*extract_filename(t_dclst *node, char **envp, t_general *gen)
{
	char	*filename;

    filename = manage_dollar((t_token *) node->data, envp, gen->exit_status);
    while (!has_space(node) && is_text(node->next))
    {
        filename = concat_filenames(filename, node->next, envp, gen);
        if (!filename)
            return (NULL);
        node = node->next;
    }
    // filename = manage_wildcards(filename, node, gen);
	return (filename);
}
