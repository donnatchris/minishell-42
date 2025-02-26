#include "../../include/minishell.h"

// Function to print error message after open() fails
// Returns -1
int	open_error(char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	perror(filename);
	free(filename);
	return (-1);
}

// Function to close redir_out
// Returns exec_tree on success, -1 on error
int	end_redir_out(t_tree *tree, char ***envp, t_general *gen, int stdout_backup)
{
	int	status;

	status = exec_tree(tree->left, envp, gen);
	if (dup2(stdout_backup, STDOUT_FILENO) == -1)
		return (close(stdout_backup), ft_perror("redir_out", "dup2 failed"));
	close(stdout_backup);
	return (status);
}

// Function to handle the redirection '>'
// Returns exec_tree on success, -1 on error
int	redir_out(t_tree *tree, char ***envp, t_general *gen, int flag)
{
	t_token	*token;
	char	*filename;
	int		fd;
	int		stdout_backup;

	if (!tree || !envp || !gen)
		return (shell_error_msg("redir_out", "invalid arguments"));
	token = (t_token *) tree->list_node->next->data;
	if (!token || token->priority != 6 || !token->start)
		return (shell_error_msg("redir_out", "invalid arguments"));
	filename = manage_dollar(token, *envp);
	if (!filename)
		return (shell_error_msg("redir_out", "filename is NULL"));
	fd = open(filename, O_CREAT | O_WRONLY | flag, 0644);
	if (fd == -1)
		return (open_error(filename));
	free(filename);
	stdout_backup = dup(STDOUT_FILENO);
	if (stdout_backup == -1)
		return (close(fd), ft_perror("redir_out", "dup failed"));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), close(stdout_backup), ft_perror("redir_out", "dup2 failed"));
	close(fd);
	return (end_redir_out(tree, envp, gen, stdout_backup));
}
