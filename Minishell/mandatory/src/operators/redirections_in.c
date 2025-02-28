#include "../../include/minishell.h"

// Function to read lines on the child process until delimiter is found
// return nothing
void    redir_heredoc_read(int pipefd[2], char *delimiter)
{
    int     i;
    char    *line;

    line = NULL;
    i = 0;
    close(pipefd[0]); // Ferme la lecture
    while (1)
    {
        i++;
        line = readline(CYAN "> " RESET);
        if (!line)
        {
            ft_putstr_fd("minishell: warning: here-document at line ", 1);
            ft_putchar_fd((char)(i + 48), 1);
            ft_putstr_fd(" delimited by end-of-file (wanted `", 1);
            ft_putstr_fd(delimiter, 1);
            ft_putstr_fd("')\n", 1);
        }
        if (strcmp(line, delimiter) == 0)	// à remplacer par ft_strncmp
            break;
        ft_putstr_fd(line, pipefd[1]);
        ft_putstr_fd("\n", pipefd[1]);
        free(line);
    }
    free(line);
    close(pipefd[1]); // ferme l'ecriture
    exit(0);
}

// Function to handle the redirection '<<'
// return exec_tree on success, return -1 on failure
int redir_heredoc(t_tree *tree, char ***envp, t_general *gen)
{
    t_token *token;
    pid_t   pid;
    int     pipefd[2];
    int     stdin_backup;

    if (!tree || !envp || !gen)
        return (shell_error_msg("redir_heredoc", "invalid arguments"));
    token = (t_token *)tree->list_node->next->data;
    if (!token || token->priority != 6 || !token->start)
        return (shell_error_msg("redir_heredoc", "invalid arguments"));
    if (pipe(pipefd) == -1)
        return (ft_perror("redir_heredoc", "pipe failed"));
    pid = fork();
    if (pid == -1)
        return (ft_perror("redir_heredoc", "fork failed"));
    if (pid == 0)
        redir_heredoc_read(pipefd, token->start);
    waitpid(pid, NULL, 0);
    close(pipefd[1]); // ferme l'ecriture
    stdin_backup = dup(STDIN_FILENO);
    if (stdin_backup == -1)
        return (close(pipefd[0]), ft_perror("redir_heredoc", "dup failed"));
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
        return (close(pipefd[0]), close(stdin_backup), ft_perror("redir_heredoc", "dup2 failed"));
    close(pipefd[0]); // ferme la lecture
    return (end_redir_in(tree, envp, gen, stdin_backup));
}

// Function to handle the redirection '<'
// Returns exec_tree on success, -1 on error
int redir_in(t_tree *tree, char ***envp, t_general *gen)
{
    t_token *token;
    char *filename;
    int fd;
    int stdin_backup;

    if (!tree || !envp || !gen)
        return (shell_error_msg("redir_in", "invalid arguments 1"));
    token = (t_token *)tree->list_node->next->data;
    if (!token || token->priority != 6 || !token->start)
        return (shell_error_msg("redir_in", "invalid arguments 2"));
    filename = manage_dollar(token, *envp, gen->exit_status);
    if (!filename)
        return (shell_error_msg("redir_in", "filename is NULL"));
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (open_error(filename));
    free(filename);
    stdin_backup = dup(STDIN_FILENO);
    if (stdin_backup == -1)
        return (close(fd), ft_perror("redir_in", "dup failed"));
    if (dup2(fd, STDIN_FILENO) == -1)
        return (close(fd), close(stdin_backup), ft_perror("redir_in", "dup2 failed"));
    close(fd);
	return (end_redir_in(tree, envp, gen, stdin_backup));
}