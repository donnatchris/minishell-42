#include "../../include/minishell.h"

static void	insert_new_node(t_dclst *new_node, t_dclst *anchor)
{
	new_node->next = anchor->next;
	new_node->prev = anchor;
	anchor->next->prev = new_node;
	anchor->next = new_node;
}

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
			shell_error_msg("insert_additionnal_nodes", "malloc failed");
			return ;
		}
		token->type = TOKEN_LITTERAL;
		token->start = ft_strdup(matching_array[i]);
		token->end = NULL;
		token->space = 1;
		token->priority = 6;
		new_node = dclst_create_node(token);
		if (!new_node)
		{
			free(token->start);
			free(token);
			shell_error_msg("insert_additionnal_nodes", "dclst_create_node failed");
			return ;
		}
		insert_new_node(new_node, current);
		current = current->next;
		i++;
	}
}

t_dclst	*find_cmd(t_dclst *node)
{
	t_dclst	*current;
	t_dclst *cmd;

	current = node;
	cmd = node;
	while (!is_tree_branch(current) && !is_eof(current))
	{
		if (is_text(current) && !is_redir(current->prev))
			cmd = current;
		current = current->prev;
	}
	return (cmd);
}

int	choose_mode(char *arg)
{
	if (arg && arg[0] == '.')
		return (W_HIDDEN);
	return (NO_HIDDEN);
}

// Function to manage the wildcards in a dynamicallly allocated array of strings
// It takes the array of strings and replaces the strings with wildcards
// with the matching filenames
// Returns the new array of strings or NULL on failure
// RETURN MUST BE FREED AFTER USE
char	*manage_wildcards(char *arg, t_dclst *node, t_general *gen)
{
	// char	*cmd;
	char	**file_array;
	char	**matching_array;
	char	pwd[PATH_MAX];

	(void) gen;
	if (((t_token *) node->data)->type != TOKEN_WORD || !ft_strchr(arg, '*'))
		return (arg);
	// cmd = ((t_token *) find_cmd(node)->data)->start;
	// if (!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
	// 	return (arg);
	file_array = get_files_in_dir(getcwd(pwd, sizeof(pwd)), choose_mode(arg));
	if (!file_array)
		return (arg);
	matching_array = extract_matching_filenames(arg, file_array);
	if (!matching_array)
		return (delete_str_tab(file_array), arg);
	delete_str_tab(file_array);
	insert_additional_nodes(node, matching_array);
	return (free(arg), matching_array[0]);
}
