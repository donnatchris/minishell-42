#include "../../include/minishell.h"

static int	is_ambiguous(char *arg, t_dclst *node)
{
	char	**file_array;
	char	**matching_array;
	char	pwd[PATH_MAX];
	int		mode;

	if (arg && arg[0] == '.')
		mode = W_HIDDEN;
	else
		mode = NO_HIDDEN;
	if (((t_token *) node->data)->type != TOKEN_WORD || !ft_strchr(arg, '*'))
		return (0);
	file_array = get_files_in_dir(getcwd(pwd, sizeof(pwd)), mode);
	if (!file_array)
		return (0);
	matching_array = extract_matching_filenames(arg, file_array);
	if (!matching_array)
		return (delete_str_tab(file_array), 0);
	delete_str_tab(file_array);
	if (count_env_size(matching_array) > 1)
	{
		shell_err_msg(arg, "ambiguous redirect");
		return (delete_str_tab(matching_array), 1);
	}
	delete_str_tab(matching_array);
	return (0);
}

// Function to add an argument to the current argument
// Returns the new argument or NULL if it fails
static char	*concat_filenames(char *filename, t_dclst *node, t_general *gen)
{
	char	*next_arg;
	char	*temp;

	next_arg = manage_dollar((t_token *) node->data, gen->envp, gen->exit_status);
	if (!next_arg)
		return (shell_err_msg("add_arg", "malloc failed"), filename);
	temp = filename;
	filename = ft_strjoin(filename, next_arg);
	if (!filename)
		shell_err_msg("add_arg", "ft_strjoin failed");
	free(temp);
	free(next_arg);
	return (filename);
}

// Function to create an array of arguments after a dclst node
// Returns the array of arguments
// RETURN MUST BE FREED AFTER USE
char	*extract_filename(t_dclst *node, t_general *gen)
{//test
	char	*filename;

    filename = manage_dollar((t_token *) node->data, gen->envp, gen->exit_status);
    while (!has_space(node) && is_text(node->next))
    {
        filename = concat_filenames(filename, node->next, gen);
        if (!filename)
            return (NULL);
        node = node->next;
    }
	if (is_ambiguous(filename, node))
		return (free(filename), NULL);
    filename = manage_wildcards(filename, node, gen);
	return (filename);
}
