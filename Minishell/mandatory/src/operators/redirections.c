#include "../../include/minishell.h"

// Function to handle the redirection '>'
// Returns exec_tree on success, -1 on error
int	redir_out(t_tree *tree, char ***envp, t_general *gen)
{
	t_token	*token;
	char	*filename;
	int		fd;
	int		status;
	int		stdout_backup;

	if (!tree || !envp || !gen)
		return (shell_error_msg("redir_out", "invalid arguments"));
	token = (t_token *) tree->list_node->next->data;
	if (!token || token->priority != 6 || !token->start)
		return (shell_error_msg("redir_out", "invalid arguments"));
	filename = manage_dollar(token, *envp);
	if (!filename)
		return (shell_error_msg("redir_out", "filename is NULL"));
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(filename);
	if (fd == -1)
		return (ft_perror("redir_out", "open failed"));
	stdout_backup = dup(STDOUT_FILENO);
	if (stdout_backup == -1)
		return (close(fd), ft_perror("redir_out", "dup failed"));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), close(stdout_backup), ft_perror("redir_out", "dup2 failed"));
	status = exec_tree(tree->left, envp, gen);
	close(fd);
	if (dup2(stdout_backup, STDOUT_FILENO) == -1)
		return (close(stdout_backup), ft_perror("redir_out", "dup2 failed"));
	close(stdout_backup);
	return (status);
}
