#include "../../include/minishell.h"

// Function to restore the standard output
// Returns status on success, -1 on error
void	end_redir_out(int stdout_backup)
{
	if (dup2(stdout_backup, STDOUT_FILENO) == -1)
		ft_perror("end_redir_out", "dup2 failed");
	close(stdout_backup);
}

// Function to find the redirection flag
// Returns O_TRUNC if the redirection is '>', O_APPEND if the redirection is '>>'
int	redir_flag(t_dclst *node)
{
	if (((t_token *) node->data)->type == TOKEN_REDIR_OUT)
		return (O_TRUNC);
	else
		return (O_APPEND);
}

// Function to get the next redirection node
// Returns the next redirection node, NULL if there is no more redirection
t_dclst	*next_redir_out(t_dclst *node)
{
	t_token	*token;

	token = (t_token *) node->data;
	while (1)
	{
		node = node->next;
		token = (t_token *) node->data;
		if (token->type == TOKEN_REDIR_OUT || token->type == TOKEN_APPEND)
			return (node);
		if (!is_text(node))
			break;
	}
	return (NULL);
}

// Function to close redir_out
// Returns exec_tree on success, -1 on error
int	redir_from_node(t_dclst *node, char ***envp, t_general *gen, int flag)
{
	t_token	*token;
	char	*filename;
	int		fd;

	token = (t_token *) node->next->data;
	if (!token || token->priority != 6 || !token->start)
		return (shell_error_msg("redir_from_node", "invalid arguments"));
	filename = manage_dollar(token, *envp, gen->exit_status);
	if (!filename)
		return (shell_error_msg("redir_out", "filename is NULL"));
	fd = open(filename, O_CREAT | O_WRONLY | flag, 0644);
	if (fd == -1)
		return (open_error(filename));
	free(filename);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), ft_perror("redir_out", "dup2 failed"));
	close(fd);
	return (0);
}

// Function to handle the redirection '>'
// Returns exec_tree on success, -1 on error
int	redir_out(t_dclst *node, char ***envp, t_general *gen)
{
	int		flag;

	if (!node || !envp || !gen)
		return (shell_error_msg("redir_out", "invalid arguments"));
	flag = redir_flag(node);
	if (redir_from_node(node, envp, gen, flag) == -1)
		return (-1);
	while (1)
	{
		node = next_redir_out(node);
		if (!node)
			break ;
		flag = redir_flag(node);
		if (redir_from_node(node, envp, gen, flag) == -1)
			return (-1);
	}
	return (0);
}

